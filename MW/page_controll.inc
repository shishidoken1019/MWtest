<?php

/**
 * Page����ȥ����륯�饹
 *
 * ����List(�̾�ǡ����μ祭��)��������Ƥ���ڡ����󥰽����פʥ����å�
 * max page���ʤɤ���ñ����ª�Ǥ���ȿ�̡��֤ä��㤱��������̤˿��餦
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('page_controll_base.inc');

class page_controll extends page_controll_base {

public function __constract()
{
  parent::__constract();
  //$this->init();
}

public function init()
{
  parent::init();
  //
  $this->clear_datas();
}

// ���Τ���������
public function set_datas($a) { $this->datas_ = $a; }
public function get_datas() { return $this->datas_; }
public function clear_datas() { $this->datas_ = array(); }

//
public function make_list()
{
  // �Ȥꤢ������˽����
  $this->set_list(array());

  // �Ȥꤢ�������ߤ�����η��������å�
  $count = count($this->get_datas());
  if ( 0 == $count) {
    return false;
  }

  // ���߻��ꤵ��Ƥ���Page�������⤫�ɤ�������
  // XXX ������Ǥʤ���硢����Page��̵�����Ĵ��
  $min = $this->get_page_num() * $this->get_par_item_num() + 1;
  if ( $count < $min ) {
    $this->set_page_num($this->get_max_page());
  }

  // �����Ѥ�List�����
  $base = $this->get_page_num() * $this->get_par_item_num();
  $datas = $this->get_datas();
  $list = array();
  for($i=0; $i < $this->get_par_item_num(); $i ++) {
    if ($count > ($base + $i) ) {
      $list[] = $datas[$base + $i];
    }
  }
  //
  $this->set_list($list);

  // �ե饰������
  if ($this->get_page_num() != 0) {
    $this->back_flg_on();
  } else {
    $this->back_flg_off();
  }

  $max = $this->get_max_page();
  if ($this->get_page_num() < $max) {
    $this->next_flg_on();
  } else {
    $this->next_flg_off();
  }

  //
  return true;
}

public function get_max_page()
{
  $count = count($this->get_datas());
  $ret =  floor(( $count + ($this->get_par_item_num() - 1)) / $this->get_par_item_num()) - 1;

 //
  return $ret;
}

// ��Page����ʤ������������Page����ɽ������������
// ɽ������Page����ָ��ߤˡޣ�Page�ޤǡפȤ���������
// XXX 1 2 3 4 5 6 7 8 9 10 �ǤϤʤ��ơ� .. [3] [4] 5 [6] [7] ... �ߤ����ʴ���
// XXX ��Ҥξ��ָ���5page�ܤǡ��ޣ�page�פä�����
public function make_range($i)
{
  //
  $ret = new max_min;
  $now = $this->get_page_num();

  // ����
  $ret->set_max( ($now + $i > $this->get_max_page())? $this->get_max_page() : $now + $i );
  $ret->set_min( ($now - $i < 0)? 0 : $now - $i );

  //
  return $ret;
}



//private:
private $datas_;	// ���Τ���������

} // end of class
