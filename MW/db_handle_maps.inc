<?php

/**
 * DB �ϥ�ɥ뽸���ѥ��饹
 *
 * ���饹����󥰴Ķ����ˤ����롢DB�ϥ�ɥ�ν�����ݻ����륯�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

//require_once('validator.inc');

class db_handle_maps {

public function __construct()
{
  //
  parent::__construct();
  $this->init();
}

//
public function init()
{
  $this->dbhs_ = array();;
}

/**
 * �᥽�åɤ�����(���)������Ū�˥᥽�å�̾
 *
 * �᥽�åɤ�����(ʣ����)���ܺ٤���������¾
 *
 * @access public��private��protected��
 * @param �� ̾�� ����
 * @return ����ͤη� ��ñ������
 */
public function get_dbh($table, $crud = 'select')
{
  // XXX
  $crud = strtolower($crud);

  // �ơ��֥�̾����³�Υ����פ�����³������
// ������¿ʬ���⡪��
  //$cplace = XXX

  // ��³�褬�����ʤ饨�顼


  // ����Ϥ��뤱����³���Ƥ��ʤ��ʤ���³����


  // �ϥ�ɥ���֤�
  //return $this->dbhs_[$cplace];
}


//private:
// dbh
private $dbhs_; // hash[Connection place] = dbh_obj

// Connection place


} // end of class
