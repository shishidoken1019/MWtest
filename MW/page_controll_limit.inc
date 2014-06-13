<?php

/**
 * Pageコントロールクラス 制限版
 *
 * 最低限のデータをDBから取り出すタイプ
 * max pageなどは取れないが、メモリ的には軽い
 * 現状、主キーが１カラムのSQLにのみ対応
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
 * DBハンドルの設定
 *
 * @access public
 * @param db_handle $o db_handleクラス(からの派生クラス)のインスタンス
 */
public function set_db($o) { $this->dbh_ = $o; }

/**
 * DBハンドルの設定
 *
 * @access public
 * @return db_handle db_handleクラス(からの派生クラス)のインスタンス
 */
public function get_db() { return $this->dbh_; }

/**
 * SQLの設定
 *
 * @access public
 * @param string $s SQL文(後ろに ; を付けない事！！)
 */
public function set_sql($s) { $this->sql_ = $s; }

/**
 * SQLの設定
 *
 * @access public
 * @return string SQL文
 */
public function get_sql() { return $this->sql_; }

/**
 * メイン処理
 *
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function make_list()
{
  // DBハンドルの取得
  $dbh = $this->get_db();
  $suobj = $dbh->get_sql_util();

  // SQL文の完成
  $from  = $this->get_page_num() * $this->get_par_item_num();
  $to = $this->get_par_item_num() + 1;
  $sql = $this->get_sql() . ' ' . $suobj->limited_range($from, $to) . ';';
//print $sql . "\n";

  // データの取得
  $res = $dbh->query($sql);
//var_dump($dbh);
//var_dump($res);

  // とりあえず全部データげとる
  $list = array();
  while($res->fetch()) {
    $list[] = $res->get_data(0);
  }

  // nextフラグ判定とデータのちょん切り
  if ($to == count($list)) {
    // ケツの要素一つ削る
    array_pop($list);
    $this->next_flg_on();
  } else {
    $this->next_flg_off();
  }

  // データを設定
  $this->set_list($list);

  // back フラグの設定
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

