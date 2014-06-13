<?php

/**
 * Page����ȥ����륯�饹
 *
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

abstract class page_controll_base {

public function __constract()
{
  $this->init();
}

public function init()
{
  $this->set_page_num(0);
  $this->set_par_item_num(1);
  $this->next_flg_off();
  $this->back_flg_off();
}

// Page���λ���
public function set_page_num($i) { $this->page_num_ = (($i+0) > 0)? $i: 0; }
public function get_page_num() { return $this->page_num_; }

// 1Page����������ǿ�
public function set_par_item_num($i) { $this->par_item_num_ = $i; }
public function get_par_item_num() { return $this->par_item_num_; }


// �������
protected function set_list($a) { $this->list_ = $a; }
public function get_list() { return $this->list_; }

//
protected function set_next_flg($b) { $this->next_flg_ = $b; }
protected function get_next_flg() { return $this->next_flg_; }
public function next_flg_on() { $this->set_next_flg(true); }
public function next_flg_off() { $this->set_next_flg(false); }
public function is_next() { return $this->get_next_flg(); }

//
protected function set_back_flg($b) { $this->back_flg_ = $b; }
protected function get_back_flg() { return $this->back_flg_; }
public function back_flg_on() { $this->set_back_flg(true); }
public function back_flg_off() { $this->set_back_flg(false); }
public function is_back() { return $this->get_back_flg(); }

//
abstract public function make_list();

/*
 * conv�ؤ�������util
 *
 * ���Ͱʲ��ν񼰤�����
 * 
<pre>
���� %%%now_page%%% Page�Ǥ���
$$$is_next$$$
<a href="?c=hogehoge&id=iddd&p=%%%next_page%%%">���򸫤�</a><br />
$$$/is_next$$$
$$$is_back$$$
<a href="?c=hogehoge&id=iddd&p=%%%back_page%%%">�������</a><br />
$$$/is_back$$$
</pre>
 *
 */
public function set_to_conv($conv)
{
  // paging�ޤ��
  $sp = new simple_put;
  if ($this->is_next()) {
    $conv->multiDic('is_next', $sp);
  }
  if ($this->is_back()) {
    $conv->multiDic('is_back', $sp);
  }
  $conv->monoDic('now_page',  $this->get_page_num());
  $conv->monoDic('next_page', $this->get_page_num() + 1);
  $conv->monoDic('back_page', $this->get_page_num() - 1);

  //
  return ;
}


//private:
private $page_num_;	// ���ߤ�Page��
private $par_item_num_;	// 1Page����������ǿ�
private $next_flg_;	//
private $back_flg_;	//
private $list_;		// ���Ϥ��Ѥ���List : Pageing���줿����

} // end of class

// max��min����ĥ��饹
class max_min
{
//public:
public function set_max($i) { $this->max_ = $i; }
public function get_max() { return $this->max_; }

public function set_min($i) { $this->min_ = $i; }
public function get_min() { return $this->min_; }

//private:
private $max_;
private $min_;
}