<?php

/**
 * DB�ޥ͡����㥯�饹
 *
 * ������ �ե����ȥ꡼
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('config.inc');
require_once('db_handle_maps.inc');

class db_manager
{

/**
 * DB�ϥ�ɥ����
 *
 * �ºݤˤϰ����η��˱����ƿ���ʬ����
 *
 * @access public
 * @param string|object $param string�ޤ���config���֥������ȤΥѥ�᥿
 * @return db_handle_object DB�ϥ�ɥ�(��)���֥�������
 */
static public function get_handle($param)
{
  // ʸ����ʤ餪���餯�ե�����̾�Ǥ������ȸ��ʤ�
  if (true === is_string($param)) {
    return db_manager::_get_handle_mono($param);
  }

  // else
  // config object�Ȥߤʤ��ƽ���
  // mono�ϤȤ������꤬�����
  $s = $param->find('db_config_path');
  if ('' !== $s) {
    // mono�ϤȤ��ƽ������ƽ�λ
    return db_manager::_get_handle_mono($s);
  }

  // else
  // XXX ���饹����󥰷Ͻ���
  if (true === $param->is('db_clustering')) {
    // XXX
    $obj = new db_handle_maps;
    $obj->set_config($param);
    return $obj;
  }

  // else
  // �ʤ��ʤ����
  return null;
}

// �Ȥꤢ����config�Ϥ����ꡣXML�Ȥ����褿��Ŭ���ˤޤȤ�ʤ���
static public function _get_handle_mono($config_filename)
{
  // ��������å�
  if(false === file_exists($config_filename)){
    return null;
  }

  // ������
  $conf = new config;
  $conf->set_file($config_filename);

  // DBMS�Υ��祤��
  $dbms = $conf->find('type');
  if ((!(strcasecmp($dbms, "postgresql")))||(!(strcasecmp($dbms, "pgsql")))) {
//print "Trap 1\n";
    require_once('f_pgsql.inc');
    $conn = new dbh_pgsql;
  } else
  if (!(strcasecmp($dbms, "mysql"))) {
//print "Trap 2\n";
    require_once('f_mysql.inc');
    $conn = new dbh_mysql;
  } else
  {
//print "Trap 3\n";
    // Ƚ����ǽ�ʤΤǥ��顼����
    return null;
  }

  // ����
  $conn->set_user($conf->find('user'));
  $conn->set_pass($conf->find('pass'));
  $conn->set_database_name($conf->find('database'));
  $conn->set_host_name($conf->find('host'));
  $conn->set_port_num($conf->find('port'));

//print "Trap1\n";
  // ��³
  // XXX ����Ƶ��Ϥˤ��Ȥ���
  if (false == $conn->rconnect()) {
//print "Trap2\n";
//print $conn->get_error_message() . "\n";
    return null;
  }
//print "Trap3\n";

  // XXX ����ѥ���ɾ�������ä��Ȥ�
  $conn->set_pass('----');

  // ����
  return $conn;
}

} // end of class

