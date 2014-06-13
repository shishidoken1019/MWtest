<?php

/**
 * DB ハンドル集合用クラス
 *
 * クラスタリング環境下における、DBハンドルの集合を保持するクラス
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
 * メソッドの説明(一行)：基本的にメソッド名
 *
 * メソッドの説明(複数行)：詳細な説明その他
 *
 * @access publicかprivateかprotectedか
 * @param 型 名前 説明
 * @return 戻り値の型 簡単な説明
 */
public function get_dbh($table, $crud = 'select')
{
  // XXX
  $crud = strtolower($crud);

  // テーブル名と接続のタイプから接続先を取得
// ここが多分キモ！！
  //$cplace = XXX

  // 接続先が不明ならエラー


  // 設定はあるけど接続していないなら接続する


  // ハンドルを返す
  //return $this->dbhs_[$cplace];
}


//private:
// dbh
private $dbhs_; // hash[Connection place] = dbh_obj

// Connection place


} // end of class

