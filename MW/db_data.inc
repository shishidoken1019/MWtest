<?php
/**
 * DBデータクラス基本
 *
 * SELECTによって帰ってくるDBデータを取り扱います
 * abstractクラスなので、必ず派生させてください
 * 
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

abstract class db_data {
//public:

  // データのfetchを行う
  // falseになったらデータ無し
  abstract public function fetch();

  // posでデータの位置を指定
  //virtual string get_data(const int pos) = 0;
  abstract public function get_data($pos);

  // 現在指定されてる１行のデータを全部取得
  //virtual vector<string> get_row(void) = 0;
  abstract public function get_row();
}

