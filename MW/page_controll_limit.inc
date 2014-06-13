<?php

/**
 * Page����ȥ����륯�饹 ������
 *
 * ����¤Υǡ�����DB������Ф�������
 * max page�ʤɤϼ��ʤ���������Ū�ˤϷڤ�
 * �������祭������������SQL�ˤΤ��б�
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('page_controll_base.inc');

class page_controll_limit extends page_controll_base {

public function __constract()
{
  parent::__constract();
  //$this->init();
}

public function init()
{
  parent::init();
}


/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @param db_handle $o db_handle���饹(������������饹)�Υ��󥹥���
 */
public function set_db($o) { $this->dbh_ = $o; }

/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @return db_handle db_handle���饹(������������饹)�Υ��󥹥���
 */
public function get_db() { return $this->dbh_; }

/**
 * SQL������
 *
 * @access public
 * @param string $s SQLʸ(����� ; ���դ��ʤ�������)
 */
public function set_sql($s) { $this->sql_ = $s; }

/**
 * SQL������
 *
 * @access public
 * @return string SQLʸ
 */
public function get_sql() { return $this->sql_; }

/**
 * �ᥤ�����
 *
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function make_list()
{
  // DB�ϥ�ɥ�μ���
  $dbh = $this->get_db();
  $suobj = $dbh->get_sql_util();

  // SQLʸ�δ���
  $from  = $this->get_page_num() * $this->get_par_item_num();
  $to = $this->get_par_item_num() + 1;
  $sql = $this->get_sql() . ' ' . $suobj->limited_range($from, $to) . ';';
//print $sql . "\n";

  // �ǡ����μ���
  $res = $dbh->query($sql);
//var_dump($dbh);
//var_dump($res);

  // �Ȥꤢ���������ǡ������Ȥ�
  $list = array();
  while($res->fetch()) {
    $list[] = $res->get_data(0);
  }

  // next�ե饰Ƚ��ȥǡ����Τ�����ڤ�
  if ($to == count($list)) {
    // ���Ĥ����ǰ�ĺ��
    array_pop($list);
    $this->next_flg_on();
  } else {
    $this->next_flg_off();
  }

  // �ǡ���������
  $this->set_list($list);

  // back �ե饰������
  if ($this->get_page_num() != 0) {
    $this->back_flg_on();
  } else {
    $this->back_flg_off();
  }

  //
  return true;
}


//private:
private $dbh_;
private $sql_;

} // end of class
