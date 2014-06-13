<?php

/**
 * ���å����ID��Ϣ���饹
 *
 * ���å����ID�κ�����key�κ���������ʤɤ����礷�ƹԤ�
 * �ʲ��η����Υơ��֥뤬���뤳�Ȥ����ꤷ�Ƥ���

���å����ID���ߤΥǡ���
���å����ID�ȥ桼��ID�Ȥ��ӤĤ��뤶�ޥ�
create table auth_session (
   id(���饤����� ID)
key sid(���å����ID)
   expire(���å����ID�μ�̿)
);
create table auth_session (
   id varchar(64) not null,
   sid varchar(64) not null,
   expire int,
   PRIMARY KEY (sid)
);

 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('session_base.inc');
require_once('tokenizer.inc');
require_once('crypt_util.inc');
require_once("crypt_factory.inc");
require_once("cgi_param.inc");

class session_id extends session_base {

public function __construct()
{
  //
  //$this->init();
  parent::__construct();
}

//
public function init()
{
  parent::init();
  $this->set_sid("");
}

//
public function set_sid($s) { $this->sid_ = $s; }
public function get_sid() { return $this->sid_; }

public function set_id($s) { $this->id_ = $s; }
public function get_id() { return $this->id_; }

protected function get_session_clump_obj()
{
  $obj = new session_id_clump;
  $obj->set_db($this->get_db());

  $wk = $this->get_config()->get_value('session_clump_table_name');
  if ("" !== $wk) {
    $obj->set_table_name($wk);
  }
  return $obj;
}

/**
 * ���å����κ���
 *
 * ���������å����ID��ȯ�Ԥ���
 *
 * @access public
 * @param string $id �������󥻥å����
 * @return boolean ����������true�����Ԥ�����false
 */
public function create($id)
{
//print "in to create \n";
  // XXX ���󤫥�ȥ饤������Τ���
  $ret = false;
  $this->set_error_string('can not create session');
  $i = 10;

  $obj = $this->get_session_clump_obj();
  $obj->set_value('id', $id, false);
  $exp = $this->get_config()->get_value('session_expire');
//print $exp . "\n";
  $obj->set_value('expire', time() + $exp, false);
//var_dump($obj);
  while($i --) {
    $sid = tokenizer::get();
    $obj->set_value('sid', $sid, false);
    if ($obj->insert()) {
      $this->set_sid($sid);
      $this->set_id($id);
      $ret = true;
      $this->set_error_string('');
      break;
    }
  }

  //
  return $ret;
}

/**
 * ���å����ΰݻ�
 *
 * key��������Ǥ���session id��ߤơ�ǧ�ڤβ��ԲĤ�Ƚ�Ǥ���
 *
 * @access public
 * @param string $key key string���̾�hidden��Cookie�����äƤ�
 * @return boolean ����������true�����Ԥ�����false
 */
public function auth($key)
{
//print "in to auth \n";
  // key�γ�ǧ
  if ("" === $key) {
    $this->set_error_string('key is empty.');
    return false;
  }

  // key����sid�����
  if (false === $this->set_key($key)) {
    $this->set_error_string('key is invalid.');
    return false;
  }
//print 'sid is ' . $this->get_sid() . "\n";

  // sid��¸�ߥ����å�
  $obj = $this->get_session_clump_obj();
  $obj->set_value('sid', $this->get_sid(), false);
  if (false === $obj->get()) {
    $this->set_error_string('session id is invalid.');
    return false;
  }
//print 'id is ' . $obj->get_value('id') . "\n";
//print 'expire is ' . $obj->get_value('expire') . "\n";
//print 'time is ' . time() . "\n";

  // ��̿�����å�
  if (time() > $obj->get_value('expire')) {
    $this->set_error_string('orver expire.');
    return false;
  }

  // ID������
  $this->set_id($obj->get_value('id'));

  // ��̿���ᤤ�Ȥ��ɤ����롩
  $flg = $this->get_config()->get_value('session_expire_flg');
  $expire = $this->get_config()->get_value('session_expire');
  if ($flg > 0) {
    // �Ĥ�ͭ�����֤λ���
    $twk = $obj->get_value('expire') - time();
//print "twk is $twk \n";
//print "exp is " . $obj->get_value('expire') . "\n";

    // ��ǧ
    // XXX ���å����ݻ����֤�50%
    if (($expire / 2) > $twk) {
//print "���å����ݻ� 50% over ( $twk ) \n";

      // �ƽ�����Ԥ�
      switch ($flg) {
        case 2:
          // ���ߤΥ��å����ID��������
          $this->del_session_id($this->get_sid());

        case 1:
          // ���������å��������
          $this->create($this->get_id());
          break;

        case 3:
          //
          $obj->set_value('expire', time() + $expire, true);
          break;

        default:
          //
          break;
      }
    }
  }

  //
  return true;
}


/**
 * key�κ���
 *
 * ���å����ID��ޤ�key���������
 * hidden�ˤ���Cookie�ˤ��衢���ܤ���key�Ǥ���ꤹ�뤳��
 * �ʤ��������˲��餫�η�(create�ޤ���set_key)��sid���Ϥ��ʤ��ȥ��顼
 *
 * @access public
 * @return string ���Ԥ������ʸ��
 */
public function get_key()
{
  // ���������å�
  $sid = $this->get_sid();
  if ("" === $sid)  {
    $this->set_error_string('sid is empty');
    return "";
  }

  // key�����
  $p = new cgi_param;

  // �ѥ�᥿��κ���
  $p->init();
  $p->add("l", crypt_util::rand_string(10,false));
  $p->add("m", $sid);
  $p->add("n", crypt_util::rand_string(10,false));

  // ����
  $key = $p->get();
//print "cgi_param is $key\n";

  // ��Ǥ�äưŹ沽
  $config = $this->get_config()->get_value('session_crypt_config');
  if ("" === $config) {
    $this->set_error_string('session crypt config is not find.');
    return "";
  }
  $en_o = crypt_factory::get_instance($config);
//var_dump($en_o);
  // �Ź沽������ʸ���󥻥å�
  $en_o->set_plain_text($key);
  // �Ź沽���롣
  $en_o->encrypt();
  // �Ź�ʸ�����������
  $key = $en_o->get_encrypted_unit();

  //
  return $key;
}

/**
 * key�μ���
 *
 * key���饻�å����ID��ID�Ȥ��������
 * ����Ū�ˤ�auth����call����뤳�Ȥ������ꤷ�Ƥʤ�
 *
 * @access public
 * @param string $key get_key�Ǻ������줿(�Ϥ���)key
 * @return boolean ��������ʤ����false
 */
public function set_key($key)
{
  //
  if ("" === $key) {
    return false;
  }

  // �Ź沽�Ϥ�����
  $config = $this->get_config()->get_value('session_crypt_config');
  if ("" === $config) {
    $this->set_error_string('session crypt config is not find.');
    return false;
  }
  $de_o = crypt_factory::get_instance($config);
  $de_o->set_encrypted_unit($key);
  $de_o->decrypt();
  $s = $de_o->get_plain_text();
//print "cgi_param is $s \n";

  // sid���Ф���
  $p = new cgi_param;
  $p->set($s);

  // ����
  $this->set_sid($p->find('m'));

  //
  return true;
}

/**
 * ���å����ID�κ��
 *
 * �������Ϥ��줿���å����ID��������
 *
 * @access public
 * @param string $sid ���å����ID
 * @return boolean �������ä���false
 */
public function del_session_id($sid)
{
  if ("" === $sid) {
    return false;
  }

  $obj = $this->get_session_clump_obj();
  $obj->set_value('sid', $sid, false);
  $obj->del();

  //
  return true;
}

//private:
private $sid_;
private $id_;
private $key_;

} // end of class

/**
 * ���å�����ѤΥơ��֥�����椹��clump
 *
 * ����Ū�ʥơ��֥륤�᡼���ϥ��å����ID��Ϣ���饹(session_id)���Ƥ��줣
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once("data_clump.inc");

class session_id_clump extends data_clump {

public function __construct()
{
  //
  //$this->init();
  parent::__construct();
}

//
public function init()
{
  parent::init();
  $this->set_element(); // �桼����Ͽ���̤����Ǥ���Ͽ
}

/**
 * ����Ū�ʾ��������
 *
 * �ơ��֥�̾����ӥ����̾�����ꤹ��
 *
 * @access protected
 * @return boolean false�ϸ������곰��
 */
protected function set_element()
{
 //
 $this->set_table_name("auth_session");

 // $inname, $cginame, $tmpname, $dbname, $keyflg
 $this->push_element("sid", "", "", "", "pk");
 $this->push_element("id", "", "", "", "");
 $this->push_element("expire", "", "", "", "");
}

//private:

} // end of class


