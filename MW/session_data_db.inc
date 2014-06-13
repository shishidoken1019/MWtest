<?php

/**
 * セッション情報をDBに書き込むクラス
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

/*
// 予想しているテーブル定義
create table session_data (
        id varchar(64) binary not null,
        data text,
        time datetime,
        PRIMARY KEY (id)
);
*/

require_once("sql_util.inc");
//require_once("security.inc");
require_once("calendar.inc");
require_once("calendar_util.inc");
require_once("session_data.inc");

class session_data_db extends session_data {
//public:

// 初期設定
public function __construct()
{
  //
  parent::__construct();
  // テーブル名をとりあえず設定
  $this->tbl_name_ = "session_data";
}

/**
 * DBハンドルの設定
 *
 * @access public
 * @param db_handle $o db_handleクラス(からの派生クラス)のインスタンス
 */
public function set_db($o) { $this->dbh_ = $o; }
/**
 * DBハンドルの取得
 *
 * @access public
 * @return db_handle db_handleクラス(からの派生クラス)のインスタンス
 */
public function get_db() { return $this->dbh_; }


/**
 * データ保存用テーブル名の設定
 *
 * @access public
 * @return string $s テーブル名
 */
public function set_tablename($s) { $this->tbl_name_ = $s; }


/**
 * DBへのsession dataの書き込み
 *
 * @access public
 * @return boolean 問題があればfalse
 */
public function write()
{

  // データの作成
  $qwk["data"] = $this->get();
  $qwk["id"] = $this->get_id();
  $qwk["time"] = calendar_util::get_now_string();

  // SQL文の生成
  $sql = sql_util::make_insert($this->tbl_name_, $qwk);

  if (($this->get_db()->query($sql))) {
    return true;
  }
//var_dump($sql);
  // NGならUPDATE
  unset ($qwk);
  $qwk["data"] = $this->get();
  $qwk["time"] = calendar_util::get_now_string();
  $where["id"] = $this->get_id();

  //
  $sql = sql_util::make_update($this->tbl_name_, $qwk, $where);
//print $sql . "\n";;
//var_dump($sql);
  if (!($this->get_db()->query($sql))) {
//print "write false\n";
    return false;
  }
  // else
//print "write true\n";
  return true;
}

/**
 * DBからsession dataへの読み込み
 *
 * @access public
 * @return boolean 問題があればfalse
 */
public function read()
{
  $sql = "SELECT data,time FROM " . $this->tbl_name_ . " WHERE id=" . security::sanitize_db_add_quote($this->get_id()) ;

//print "validity term is " . $this->get_validity_term() . "\n";

  if ($this->get_validity_term() > 0) {
    // 有効期限の作成
    $cal = new calendar;
    $cal->set_now_date();
    $cal->set_epoc($cal->get_epoc() - $this->get_validity_term());

    $sql .= " and time >= '" . $cal->get_string("-") . "'";
  }
  $sql .= ";";
//print $sql . "\n";

  if (!($data = $this->get_db()->query($sql))) {
    return false;
  }
  if (!($data->fetch())) {
    return false;
  }

  //
//var_dump($data->get_data(0));
  $this->set($data->get_data(0));
//var_dump($this);
//print $data->get_data(1) . "\n";
  return true;
}


/**
 * DB内にあるsession dataの削除
 *
 * メモリ上のデータを削除する場合は initメソッドで
 *
 * @access public
 * @return boolean 問題があればfalse
 */
public function del() {
  $where["id"] = $this->get_id();
  $sql = sql_util::make_delete($this->tbl_name_, $where);
//print $sql . "\n";
  return $this->get_db()->query($sql);
}

/**
 * セッションIDの存在チェック
 *
 * @access public
 * @return boolean 存在していたらtrue
 */
public function is_session() {
  $sql = "SELECT count(*) FROM " . $this->tbl_name_ . " WHERE id=" . security::sanitize_db_add_quote($this->get_id()) ;
//print $sql . "\n";

  if (!($data = $this->get_db()->query($sql))) {
//print "is_session NG 1\n";
    return false;
  }
  if (!($data->fetch())) {
//print "is_session NG 2\n";
    return false;
  }

  //
  if ( 0 == $data->get_data(0)) {
//print "is_session NG 3\n";
    return false;
  }

  //
//print "is_session OK\n";
  return true;
}

/**
 * 上書きしないように注意しながらのwrite
 *
 * @access public
 * @return boolean 問題があればfalse。同一セッションID名でのレコードがあるときもfalse
 */
public function fix_session()
{
//print "fix Trap 1\n";
  // とりあえずisで確認する
  if (true === $this->is_session()) {
    // 存在してたらNGってことでfalseをかえす
//print "is_session true\n";
    return false;
  }

//print "fix Trap 2\n";
  // INSERTでもう一度チェックする
  $qwk["data"] = "";
  $qwk["id"] = $this->get_id();
  $qwk["time"] = calendar_util::get_now_string();

  $sql = sql_util::make_insert($this->tbl_name_, $qwk);
//print "$sql \n";

  if (($this->get_db()->query($sql))) {
    // INSERTできたのでTRUE
    return true;
  }
//print "insert invalid\n";

  // しくじってるっぽいのでFalse
  return false;
}

//private:
private $dbh_; // DBハンドル
private $tbl_name_;
} // end of class

