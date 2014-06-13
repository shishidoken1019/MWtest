<?php

/**
 * Pageコントロールクラス
 *
 * 「全List(通常データの主キー)を取得してからページング処理」なロジック
 * max page数などが簡単に捕捉できる反面、ぶっちゃけメモリを大量に食らう
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

// 全体の要素配列
public function set_datas($a) { $this->datas_ = $a; }
public function get_datas() { return $this->datas_; }
public function clear_datas() { $this->datas_ = array(); }

//
public function make_list()
{
  // とりあえず先に初期化
  $this->set_list(array());

  // とりあえず現在の配列の件数をチェック
  $count = count($this->get_datas());
  if ( 0 == $count) {
    return false;
  }

  // 現在指定されているPageが範疇内かどうか決定
  // XXX 範疇内でない場合、最大Pageに無理やり調整
  $min = $this->get_page_num() * $this->get_par_item_num() + 1;
  if ( $count < $min ) {
    $this->set_page_num($this->get_max_page());
  }

  // 出力用のListを抽出
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

  // フラグの設定
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

// 全Pageじゃなくて特定の幅でPage数を表示したい時用
// 表示するPage数を「現在に±ｎPageまで」とかいう時用
// XXX 1 2 3 4 5 6 7 8 9 10 ではなくて、 .. [3] [4] 5 [6] [7] ... みたいな感じ
// XXX 上述の場合「現在5page目で、±２page」って設定
public function make_range($i)
{
  //
  $ret = new max_min;
  $now = $this->get_page_num();

  // 設定
  $ret->set_max( ($now + $i > $this->get_max_page())? $this->get_max_page() : $now + $i );
  $ret->set_min( ($now - $i < 0)? 0 : $now - $i );

  //
  return $ret;
}



//private:
private $datas_;	// 全体の要素配列

} // end of class

