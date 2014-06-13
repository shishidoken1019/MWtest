<?php

/**
 * MVC Model部分 色々できるよ用基底クラス
 *
 * このクラス直使うことはないと思うんだけどなぁ
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model.inc');
require_once('session.inc');
require_once('mobile_info.inc');
require_once('conv_util.inc');

abstract class base_model_rich extends base_model {

//public:
public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}


//初期化
public function init(){
  parent::init();
  $this->set_session_obj(null);
  $this->auth_state_off();
  $this->set_id('');
  $this->set_authtype_auth();
  $this->with_mobile_off();
}

//
protected function set_session_obj($o) { $this->session_obj_ = $o; }
public function get_session_obj() { return $this->session_obj_; }

//
protected function set_sconfig($o) { $this->sconfig_ = $o; }
protected function get_sconfig() { return $this->sconfig_; }

//
protected function set_authtype($i) { $this->authtype_ = $i; }
protected function get_authtype() { return $this->authtype_; }
protected function _is_authtype($i)
{
  if ($i == $this->get_authtype()) {
    return true;
  }
  // else
  return false;
}
public function set_authtype_auth() { $this->set_authtype(1); }
public function is_authtype_auth() { return $this->_is_authtype(1); }
public function set_authtype_ambiguous_auth() { $this->set_authtype(2); }
public function is_authtype_ambiguous_auth() { return $this->_is_authtype(2); }

//
public function with_mobile_on() { $this->with_mobile_ = 1; }
public function with_mobile_off() { $this->with_mobile_ = 2; }
public function is_with_mobile()
{
//var_dump($this->with_mobile_);
  if (1 === $this->with_mobile_) {
    return true;
  }
  // else
  return false;
}

/**
 * ユーザIDを取得する
 *
 * ユーザIDとは
 * ・通常においては内部ユーザID
 * ・匿名セッションにおいてはトークン
 * ・携帯に関してはuidまたはサブスクライバIDの類
 * ・DoCoMoについては 公式フラグ が立っていればcgi requestのuid
 * を指すものとする
 *
 * @access public
 * @return string ユーザID 存在しない場合空文字
 */
public function get_id() { return $this->id_; }
protected function set_id($o) { $this->id_ = $o; }

/**
 * 認証状態のチェック
 *
 * @access public
 * @return boolean 認証状態ならtrue、非認証状態ならfalse
 */
public function is_auth() { return $this->get_auth_state(); }

//
public function get_auth_state() { return $this->auth_state_; }
protected function set_auth_state($b) { $this->auth_state_ = $b; }
public function auth_state_on() { $this->set_auth_state(true); }
public function auth_state_off() { $this->set_auth_state(false); }

/**
 * 認証本体
 *
 * 結果は内部変数に格納されるため、return自体はvoid
 *
 * @access protected
 */
protected function _authorization()
{
//print "_authorization Trap1\n";
  // 携帯の場合
  if ($this->is_with_mobile()) {
//print "do_auth_mobile_site\n";
    $ret = $this->do_auth_mobile_site();
  } else {
  // PCの場合
//print "do_auth\n";
    $ret = $this->do_auth();
  }
  //
  if (true === $ret) {
    $this->auth_state_on();
  } else {
    $this->auth_state_off();
  }
//print "_authorization Trap99\n";

  //
  return;
}


/**
 * 認証を試みる(ID＋password系
 *
 * 通常のセッションからの認証
 * 対応するものに「公式サイト系の認証」がある
 *
 * @access public
 * @return boolean 認証状態ならtrue、非認証状態ならfalse
 */
public function do_auth() {
//print "base_model_auth execute Trap 1\n";
  //
  $req = $this->get_cgi_request();

  // セッションクラスげと
  $obj = new session;
  $obj->set_config_filename($this->get_config()->find('session_config'));
  $obj->set_db($this->get_db());
  $this->set_sconfig($obj->get_config());

  // key stringげと
  // XXX 順番は固定でpost、Cookie、get。あとで可変にしたいなぁ。
  // 現状のモードの退避
  $pm = $req->get_priority();
  $key = "";
  if (true === $this->get_sconfig()->is_value('auth_key_get')) {
    $req->set_only_get();
    $name = $this->get_sconfig()->get_value('auth_key_get_name');
    $value = $req->find($name);
    if ("" !== $value) { $key = $value; }
  }
  if (true === $this->get_sconfig()->is_value('auth_key_post')) {
    $req->set_only_post();
    $name = $this->get_sconfig()->get_value('auth_key_post_name');
    $value = $req->find($name);
    if ("" !== $value) { $key = $value; }
  }
  if (true === $this->get_sconfig()->is_value('auth_key_cookie')) {
    $name = $this->get_sconfig()->get_value('auth_key_cookie_name');
    $value = $req->find_cookie($name);
//print "cookie value is $value \n";
    if ("" !== $value) { $key = $value; }
  }
  // 戻す
  $req->set_priority($pm);
//print "key = $key \n";
 
  // keyがなければ非認証状態
  if ("" === $key) {
    $this->auth_state_off();
    return false;
  }

  // 認証エラーならやっぱり非認証
  $ret = $obj->auth($key);
  if (false === $ret) {
    $this->auth_state_off();
    return false;
  }

  // Cookieなら、keyの設定をしておく
  if (true === $this->get_sconfig()->is_value('auth_key_cookie')) {
    $name = $this->get_sconfig()->get_value('auth_key_cookie_name');
    setcookie($name, $obj->get_key());
  }

  //
  $this->set_session_obj($obj);
  $this->set_id($this->get_session_obj()->get_id());
  $this->auth_state_on();
  return true;
}

/**
 * 携帯サイトとして認証を試みる
 *
 * XXX 認証のtrue falseはユーザテーブルに存在するかどうかでみる
 * ぶっちゃけ毎回ログインしてる感じだよねぇこれって
 *
 * @access public
 * @return boolean 認証状態ならtrue、非認証状態ならfalse
 */
public function do_auth_mobile_site() {
  // 初期化
  $this->set_id('');
  $this->auth_state_off();

  // IDの取得
  $miobj = new mobile_info;

  $uid = '';
  if ( (true === $miobj->is_docomo())&&((true === $this->is_official_site())|| ( (false === empty($_SERVER['HTTPS']))&&('off' !== $_SERVER['HTTPS']) )) ) {
//print "official docomo\n";
    // DoCoMoかつ
    // 公式、またはSSLによる接続の場合
    $uid = $this->get_cgi_request()->find('uid');
  } else {
//print "any mobile\n";
    // それ以外
    $uid = $miobj->get_sid();
  }

  // XXX チョイ場当たり対応。
  // XXX PCでかつuidの類がuser-agentに設定されてなければパラメタ uid を使う
  // XXX user-agentにがんばって設定してるならそっち優先したいからelseぢゃないif
  if (('' === $uid) && (false === $miobj->is_mobile())) {
    $uid = $this->get_cgi_request()->find('uid');
  }
//var_dump($uid);
  if ("" === $uid) {
//print "uid is null\n";
    // XXX 単純なfalseぢゃなくて、なにか小細工したくなるかも
    return false;
  }

  // げとれたuidを設定
  $this->set_id($uid);

  // ユーザテーブル確認
  $cobj = $this->get_config();
  // SELECT id FROM table WHERE uid=$id and del_flg = 0;
  // XXX 後で書き直す〜 重複いや orz
  if ("" !== $cobj->find('official_site_user_del_flg')) {
    $sql = sprintf('SELECT %s FROM %s WHERE %s=%s and %s=%s;',
                    $cobj->find('official_site_user_id'),
                    $cobj->find('official_site_user_table'),
                    $cobj->find('official_site_user_uid'),
                    security::sanitize_db_add_quote($uid),
                    $cobj->find('official_site_user_del_flg'),
                    security::sanitize_db_add_quote($cobj->find('official_site_user_del_flg_value'))
                  );
  } else {
    $sql = sprintf('SELECT %s FROM %s WHERE %s=%s;',
                    $cobj->find('official_site_user_id'),
                    $cobj->find('official_site_user_table'),
                    $cobj->find('official_site_user_uid'),
                    security::sanitize_db_add_quote($uid)
                  );
  }
//print $sql . "\n";
  //
//var_dump($this->get_db());
  $res = $this->get_db()->query($sql);
  if (is_null($res)) {
      return false;
  }
  if (false === $res->fetch()) {
    return false;
   }

  // 情報とれたっぽなので、処理
  $this->auth_state_on();

  //
  return true;
}


/**
 * 認証必須系においてNGだった場合の遷移処理
 *
 * @access public
 */
public function auth_ng_process() {
  //
  $this->recursive_on();
  // 設定がなければindexにつっかえす
  $command = 'index';
  if (false === is_null($this->get_sconfig())) {
    if ("" !== $this->get_sconfig()->get_value('auth_error_return_command')) {
      $command = $this->get_sconfig()->get_value('auth_error_return_command');
    }
  }
//var_dump($this->get_sconfig());

  // コマンド名設定
  $this->set_recursive_command($command);

  // テンプレートファイル情報を一旦削除
  $this->set_tmp_filename('');

  //
  return ;
}

/**
 * 公式サイトってconfigに書いてあるかどうかチェック
 *
 * XXX あとで「外から問答無用設定」できるようにしないとねぇ…
 *
 * @access public
 * @return boolean 公式サイトならtrue、非公式ならfalse
 */
public function is_official_site() {
  $s = $this->get_config()->find('official_site');
  if(preg_match("/^(yes|y|ok|true|on|1)$/i", $s)) {
    return true;
  }
  // else
  return false;
}

/**
 * modelマウントポイント
 *
 * 適切な認証チェックとかやって適切なメソッドにぶんなげる
 *
 * @access public
 */
public function initialize() {
//print "Trap 1\n";
  // authorization チェック
  // はじくか外にってか別メソッドに
  $this->_authorization();
}
public function execute() {
  // 一応念のためのマウントポイント
  $ret = $this->execute_rich_mount1();
  if (false === $ret) {
    $this->auth_ng_process();
    return;
  }

  // authorization チェック
  // はじくか外にってか別メソッドに
  //$this->_authorization();

  // 一応念のためのマウントポイント
  $ret = $this->execute_rich_mount2();
  if (false === $ret) {
    $this->auth_ng_process();
    return;
  }

  // OKだったりNGだったり
  // authの場合
  if ($this->is_authtype_auth()) {
    if (false === $this->is_auth()) {
      // エラー
      $this->auth_ng_process();
      return;
    }
    // else
    $ret = $this->execute_auth();
  } else {
    // XXX$this->is_authtype_ambiguous_auth() やらないよとりあえず
    $ret = $this->execute_ambiguous_auth();
    // XXX ついでにセット
    $sp = new simple_put;
    if (true === $this->is_auth()) {
      $this->get_conv()->multiDic('is_auth', $sp);
    } else {
      $this->get_conv()->multiDic('is_noauth', $sp);
    }
  }

  // 一応念のためのマウントポイント
  $ret = $this->execute_rich_mount3();
  if (false === $ret) {
    $this->auth_ng_process();
    return;
  }
  //
  return ;
}


// 何かやりたい時用
public function execute_rich_mount1() { return true; }
public function execute_rich_mount2() { return true; }
public function execute_rich_mount3() { return true; }

//private:
private $session_obj_;		// 認証クラスインスタンス
private $auth_state_;		// 認証状態
private $sconfig_;		// 認証configのクラスインスタンス
private $id_;			// ユーザを識別するためのID
private $authtype_;		// 1:auth必須 2:authしてもしなくても
private $with_mobile_;		// 1:with_mobile  2:without_mobile

} // end of class

