<?php

/**
 * データの塊(clump)クラス
 *
 * 実際には、データを固まりで扱い、かつ
 * ・cgiインタフェースとのやり取り
 * ・テンポラリテーブルとのやり取り
 * ・DBとのやり取り
 * を統括する。
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('basis_clump.inc');
require_once('tokenizer.inc');
require_once('calendar_util.inc');
require_once('security.inc');
require_once('sql_util.inc');
require_once('session_data_db.inc');
require_once('conv_util.inc');

class data_clump extends basis_clump
{
//public:

//
public function __construct()
{
  parent::__construct();
  //$this->init();
}

// 初期化
public function init()
{
  //
  parent::init();

  //
  $this->tblname_ = "";         // 正規DBテーブル名
  $this->dbh_ = null;           // DBハンドル
  //
  $this->tmpname_ = "";         // テンポラリテーブル名
  $this->tmp_key_ = "";         // テンポラリテーブル用キー

  //
  $this->nokeyname_ = array();  // Keyではない名前一式
  $this->keyname_ = array();    // Keyになってる名前一式

  //
  $this->cgi_name_ = array();   // CGI上の名前
  $this->tmp_name_ = array();   // テンポラリテーブル上の名前
  $this->db_name_ = array();    // 正規DB上の名前
}


/**
 * DBテーブル名の設定
 *
 * @access public
 * @param string $s テーブル名
 */
public function set_table_name($s) { $this->tblname_ = $s; }
/**
 * DBテーブル名の取得
 *
 * @access public
 * @return string テーブル名
 */
public function get_table_name() { return $this->tblname_; }


/**
 * テンポラリテーブル名の設定
 *
 * データを一時的に格納するためのもの
 *
 * @access public
 * @param string $s テーブル名
 */
public function set_session_table_name($s) { $this->tmpname_ = $s; }
/**
 * テンポラリテーブル名の取得
 *
 * @access public
 * @return string テーブル名
 */
public function get_session_table_name() { return $this->tmpname_; }



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

// publicか微妙なのでちとコメントは書かない
public function set_tmp_key($s) { $this->tmp_key_ = $s; }
public function get_tmp_key() { return $this->tmp_key_; }
// keyをトークナイザで作成する
public function make_tmp_key() { $this->set_tmp_key(tokenizer::get()); }

// XXX 以下、publicだけどprotectedっぽいのでコメントだけ書かないどく

// dbでの要素名のアクセサ
public function set_db_name($n, $v) { $this->db_name_[$n] = $v; }
public function get_db_name($n) { return $this->db_name_[$n]; }
// テンポラリテーブルでの要素名のアクセサ
public function set_tmp_name($n, $v) { $this->tmp_name_[$n] = $v; }
public function get_tmp_name($n) { return $this->tmp_name_[$n]; }
// cgi form名のアクセサ
public function set_cgi_name($n, $v) { $this->cgi_name_[$n] = $v; }
public function get_cgi_name($n) { return $this->cgi_name_[$n]; }
// keyname関連
public function push_keyname($n) { $this->keyname_[] = $n; }
public function get_all_key_names()   { return $this->keyname_; }

public function push_nokeyname($n) { $this->nokeyname_[] = $n; }
public function get_all_no_key_names() { return $this->nokeyname_; }


/**
 * データセッタ
 *
 * データを変更。flgの指示によってはDB変更も連動させる
 * XXX 主キーに対する挙動が未設定
 *
 * @access public
 * @param string $name 名前
 * @param string $value 設定する値
 * @param boolean $flg 変更用フラグ。trueでDBの更新も行う。デフォルトはtrue
 * @return boolean 問題があればfalse
 */
public function set_value($name, $value, $flg = true)
{
//print "$name , $value ; \n";
  // 存在チェック
  if( !($this->is_name($name)) ) {
    return false;
  }

  // データの設定
  $this->set_data($name, $value);

  // flgが true の場合はDBも更新
  if ($flg) {
    $wk = $this->get_db_name($name) . "=" . security::sanitize_db_add_quote($value);
    //
    return $this->_mono_set_db($wk);
  }

  // flg が false なら、DBを更新せずに終了
  return true;
}

/**
 * データゲッタ
 *
 * データを取得。存在しない場合空文字。
 * データとしての空文字なのか存在しないのかが重要な場合はis_name使って
 *
 * @access public
 * @param string $name 名前
 * @return string 値。データがなければ空文字
 */
public function get_value($name)
{
  // XXX 存在チェックはget_dataメソッドに依存
  return $this->get_data($name);
}

/**
 * 要素の設定
 *
 * data一式設定。
 * key_flgは、key|pk|k|ok|true|on のいずれかでkeyであるとみなす
 * XXX 一応publicだけど、生で設定するのちょいとやだよねぇ？
 *
 * @access public
 * @param string $inname 内部呼称用の名前
 * @param string $cginame CGI Formでの名前
 * @param string $tmpname テンポラリテーブル上での名前
 * @param string $dbname DB上での名前
 * @param string $keyflg PKの場合、ここをpkにする
 * @return boolean 何か問題があればfalse
 */
public function push_element
($inname, $cginame = "", $tmpname = "", $dbname = "", $keyflg = "")
{

  // 最低でもinnameはあること。なきゃNG
  if( !isset($inname)) {
    return false;
  }
  if( "" === $inname) {
    return false;
  }

  // 二重にcallしていないかチェック
  // XXX 上書きしないで無視する
  if (true === $this->is_name($inname)) {
    return true;
  }

  // まずnameを登録
  parent::push_element($inname);

  // CGI名称の設定
  if ("" === $cginame) {
    $cginame = $inname;
  }
  $this->set_cgi_name($inname, $cginame);

  // テンポラリテーブル名称の設定
  if ("" === $tmpname) {
    $tmpname = $inname;
  }
  $this->set_tmp_name($inname, $tmpname);

  // 正規DB名称の設定
  if ("" === $dbname) {
    $dbname = $inname;
  }
  $this->set_db_name($inname, $dbname);

  // keyの判定
  if(preg_match("/^(key|pk|k|ok|true|on)$/i", $keyflg)) {
    $this->push_keyname($inname);
  } else {
    $this->push_nokeyname($inname);
  }
  //
  return true;
}

/**
 * チェックメソッド
 *
 * データ全体のチェックを行う。まぁvalidator
 * このクラス自体はVirtualレベルの仮実装。後々に向けて用なので。
 *
 * @access public
 * @return boolean 常にtrue
 */
public function check() { return true; }

/**
 * CGIからの情報の吸い取り
 *
 * DBへの自動格納は行わない!!
 *
 * @access public
 * @param cgi_request $req cgi_requestクラスのインスタンス
 * @param boolean $empty_overwrite_flg 空文字の上書きフラグ trueにすると空なら空文字を上書きする
 * @return boolean 何か問題があればfalse
 */
public function set_from_cgi($req, $empty_overwrite_flg = false)
{
  // 全データを取得
  foreach($this->get_all_names() as $name) {
    // 情報の(とりあえずの)格納
    $wk = $req->find($this->get_cgi_name($name));
    // 上書きフラグが false で
    if (false === $empty_overwrite_flg) {
      if ("" === $wk) {
        continue;
      }
    }
    //
    $this->set_value($name, $wk, false);
//print "$name <= $wk <br />\n";
  }

//print "set_from_cgi <BR>\n";
//print_r($this->data_);
//print "<BR>\n";

  return true;
}

//
protected function _make_session_instance()
{
  // オブジェクト生成＆基本データの挿入
  $se = new session_data_db;
  $se->init();
  $se->set_db($this->get_db());
  $se->set_id($this->get_tmp_key());
  if ("" !== $this->get_session_table_name()) {
    $se->set_tablename($this->get_session_table_name());
  }

  //
  return $se;
}

/**
 * テンポラリテーブルへのデータの格納
 *
 * @access public
 * @param session_data_obj $se セッションdataクラス。nullなら新規に作る
 * @return boolean 何か問題があればfalse
 */
public function set_to_tmp($se = null)
{
  if (true === is_null($se)) {
    // キーチェック
    if("" === $this->get_tmp_key()) {
      // キーが設定されてなければ作る
      // XXX エラーのほうがよいか？？？
      $this->make_tmp_key();
    }

    // オブジェクト生成＆基本データの挿入
    $se = $this->_make_session_instance();
  }

  // 現在情報を読み込む
  $se->read();

  // オブジェクトに全データを突っ込む
  foreach($this->get_all_names() as $name){
    // 格納
    $se->add_once($this->get_tmp_name($name), $this->get_value($name));
  }

  // 書き込み
  return $se->write();
}


/**
 * テンポラリテーブルから情報を引っ張る
 *
 * tmp_keyの設定がない場合はNGになるので注意
 *
 * @access public
 * @param session_data_obj $se セッションdataクラス。nullなら新規に作る
 * @return boolean 何か問題があればfalse
 */
public function set_from_tmp($se = null)
{
  
  if (true === is_null($se)) {
    // キーチェック
    if("" === $this->get_tmp_key()) {
      return false;
    }

    // オブジェクト生成＆基本データの挿入
    $se = $this->_make_session_instance();
  }

  // 全データの取得
  if(!($se->read())) {
    return false;
  }

  // オブジェクトに全データを突っ込む
  foreach($this->get_all_names() as $name) {
    // 格納
    $wk = $se->find($this->get_tmp_name($name));
    $this->set_value($name, $wk, false);
  }

  //
  return true;
}

/**
 * 正規DBへの登録へのラッパー
 *
 * 実態はset_to_db
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function set() { $this->set_to_db(); }

/**
 * 正規DBへの登録
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function set_to_db()
{
//print "into set <br />\n";
  // 基本はinsert
  if (!($this->insert())) {
//print "insert error <br />\n";
    // エラーならUpdate
    if (!($this->update())) {
//print "update error <br />\n";
      return false;
    }
  }
//print "fin set <br />\n";
  //
  return true;
}

// where作成用
// where配列をhashで作ってる
protected function _make_where()
{
  $where = array();
  foreach($this->get_all_key_names() as $name) {
    $where[ $this->get_db_name($name) ] = $this->get_data($name);
  }
  //
  return $where;
}

/**
 * データのinsert
 *
 * 塊全体をinsertする
 * DBハンドル未設定の場合「あえて」PHPエラー出すようにしてる
 *
 * @access public
 * @param boolean $del_flg 削除時用特殊フラグ。意識しないこと!!
 * @return boolean 何か問題があればfalse
 */
public function insert($del_flg = false)
{
  // 全データの格納
  $value = array();
  foreach($this->get_all_names() as $name) {
    $value[ $this->get_db_name($name) ] = $this->get_data($name);
  }
  // XXX
  if (true === $del_flg) {
    // データの追加
    $value['delete_date'] = calendar_util::get_now_string();
    // SQLの発行
    $sql = sql_util::make_insert($this->get_table_name() . '_delete', $value);
  } else {
    // SQLの発行
    $sql = sql_util::make_insert($this->get_table_name(), $value);
  }

  //
  return $this->_sql($sql);
}

/**
 * データのupdate
 *
 * 塊全体をupdateする
 * DBハンドル未設定の場合「あえて」PHPエラー出すようにしてる
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function update()
{
  // where部分の設定
  $where = $this->_make_where();

  // value部分の設定
  $value = array();
  foreach($this->get_all_no_key_names() as $name) {
    $value[ $this->get_db_name($name) ] = $this->get_data($name);
  }

  // SQLの発行
  $sql = sql_util::make_update($this->get_table_name(), $value, $where);

  //
  return $this->_sql($sql);
}


/**
 * データのdelete
 *
 * 塊全体をdeleteする
 * DBハンドル未設定の場合「あえて」PHPエラー出すようにしてる
 * テーブル名_deleteというテーブルがある場合、全情報をそっちにinsert
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function del()
{
  // where部分の設定
  $where = $this->_make_where();

  // 削除テーブルにinsert
  // XXX フラグか何かもつかなぁ？ 現状insertしくっても無視、程度なのだが
  $this->insert(true);

  // SQLの発行
  $sql = sql_util::make_delete($this->get_table_name(), $where);
  //
  return $this->_sql(sql_util::make_delete($this->get_table_name(), $where));
}

/**
 * データ１つのupdate
 *
 * あんまり散発的にやるとDBに負荷かかるから注意してね
 *
 * @access public
 * @param string $sql_p sqlのパーツ。具体的にはsetに渡すSQL文そのもの
 * @return boolean 何か問題があればfalse
 */
public function _mono_set_db($sql_p)
{
  //
  $where = $this->_make_where();

  // XXX 場当たり
  $sql = "UPDATE " . $this->get_table_name() . " SET " . $sql_p . " WHERE " . sql_util::make_where($where) . ";";
//print $sql . "\n";

  //
  return $this->_sql($sql);
}

/*
 * SQL発行
 *
 * XXX SELECTでは使えないことに注意!!
 * publicにはしとくけど基本protectedだよねぇ
 *
 */
public function _sql($sql)
{
//print $sql . "\n";

  //
  $ret = $this->get_db()->query($sql);
//var_dump($ret);
  if (is_null($ret)) {
    return false;
  }
  if (false === $ret) {
    return false;
  }

  return true;
}

/**
 * 情報全体の取得
 *
 * 当然ながらkey設定しないとNGになります。
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function get()
{
  // where部分の作成
  $where = $this->_make_where();
  //
  return $this->_get($where);
}

/**
 * pkによらない情報全体の取得
 *
 * pkではなく「現在設定されている値」からwhere句をつむぎます
 *
 * @access public
 * @return boolean 何か問題があればfalse
 */
public function get_nopk()
{
  //
  $cols = $this->get_all_names();

  // 値があるものをandでwhereとする
  $where = array();
  foreach ($cols as $col) {
    //
    if ("" !== $this->get_value($col)) {
      $where[$col] = $this->get_value($col);
    }
  }
  //
  return $this->_get($where);
}

/**
 * 情報全体の取得本体
 *
 * 当然ながらkey設定しないとNGになります。
 * XXX keyが「pk」から「値が設定されているもの」に変更になりました
 *
 * @access public
 * @param array &$where select時に使うwhere句作成用のhash配列
 * @return boolean 何か問題があればfalse
 */
public function _get(array &$where)
{
  // SELECT カラムの作成
  $col = implode(",", $this->get_all_names());

  // SQLの作成
  $sql = "SELECT " . $col . " FROM " . $this->get_table_name() . " WHERE " . sql_util::make_where($where) . ";";
//print $sql . "\n";

  // SQLの発行
//print "---------------------\n";
//var_dump($this->get_db());
//print "---------------------\n";
  $res = $this->get_db()->query($sql);
//print $sql . "\n";
//var_dump($res);
  if (is_null($res)) {
    return false;
  }
  if (false === $res) {
    return false;
  }
  // データがなければNG
  if (false === $res->fetch()) {
    return false;
  }
//print "<br />Trap1 <br />\n";
  $count = 0;
  $all_names = $this->get_all_names();
//print_r($all_names);
//print "<br />\n";

  foreach($all_names as $name) {
//print "Trap2 <br />\n";
    // データをインスタンス内に保持
    $this->set_value($name, $res->get_data($count), false);
//print "$name is " . $res->get_data($count) . "\n";

    //
    $count ++;
  }

  //
  return true;
}

/**
 * 情報をハッシュ配列にして取得
 *
 * @access public
 * @return map ハッシュ配列
 */
public function get_all_data_to_hash()
{
  $ret = array();
  // まずはすべての項目名をげと
  $all_names = $this->get_all_names();

  // で、設定
  foreach($all_names as $name) {
    $ret[$name] = $this->get_value($name);
  }
  //
  return $ret;
}

/**
 * monoDicでデータ一式を設定する
 *
 * XXX 平たくお便利系メソッド
 * XXX get_all_data_to_hashのデータを基準にしてみる：この方が継承時に楽
 *
 * @access public
 * @param convインスタンス $conv 置換エンジンインスタンス
 */
public function set_all_to_conv($conv)
{
  // クラス名取得
  $cn = get_class($conv);
//var_dump($cn);

  foreach($this->get_all_data_to_hash() as $name => $value) {
    // 単置換用
    if ('f_conv' === $cn) {
      $conv->monoDic($name, security::sanitize_html($value));
    } else
    if ('secure_conv' === $cn) {
      $conv->monoDic($name, $value);
    }
    // XXX else …どうする？
    // XXX 後でsmarty実装でも入れるかしらん？
  }

  //
  return true;
}


/**
 * 指定されたカラムに現在日付を設定
 *
 * この処理において自動反映フラグがデフォtrueなのは変なので
 * デフォはfalseにしてある
 *
 * @access public
 * @param string $name 現在日付を設定したいカラム名
 */
public function set_value_nowdate($name, $flg = false)
{
  return $this->set_value($name, calendar_util::get_now_string(), $flg);
}


/**
 * 指定されたカラムにトークン設定
 *
 * この処理において自動反映フラグがデフォtrueなのは変なので
 * デフォはfalseにしてある
 * トークン名はget_valueでげとって〜
 *
 * @access public
 * @param string $name トークンを設定したいカラム名
 */
public function set_value_token($name, $flg = false)
{
  return $this->set_value($name, tokenizer::get(), $flg);
}

/**
 * set_all_to_convされたconvインスタンスを取得する
 *
 * secure_convインスタンスを返す。
 * 後で、smarty系のインスタンスも返せるように作り直すか？
 *
 * @access public
 * @param string $name トークンを設定したいカラム名
 * @return convインスタンス 置換エンジンインスタンス
 */
public function get_conv($class_name = 'secure_conv')
{
  //
  $o = new $class_name;

  //
  $this->set_all_to_conv($o);

  //
  return $o;
}

/**
 * radioボタンを設定する
 *
 * @access public
 * @param array $names radioボタンとして設定したい値
 * @param convインスタンス $conv 置換エンジンインスタンス
 */
public function set_radio($names, $conv)
{
  foreach($names as $name) {
    conv_util::monoDicChecked($conv, $name, $this->get_value($name));
  }
}



//private:
private $dbh_;          // DBハンドル

private $tmpname_;      // テンポラリテーブル名
private $tmp_key_;      // テンポラリテーブル用キー

private $tblname_;      // 正規DBテーブル名(Keyはkeyname_で確認)

private $cgi_name_;     // CGI上の名前:hashは論理名で
private $tmp_name_;     // テンポラリテーブル上の名前:hashは論理名で
private $db_name_;      // 正規DB上の名前:hashは論理名で

private $nokeyname_;    // Keyではない論理名一式
private $keyname_;      // Keyになってる論理名一式

} // end of class

