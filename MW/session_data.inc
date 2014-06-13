<?php

/**
 * セッションデータ保持クラス
 *
 * セッション情報を保持するクラス
 * 実際にはVirtualなクラスなので継承先じゃないとインスタンス作れない〜
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once("cgi_param.inc");

// XXX データ形式的にこれが便利なのでcgi_paramから継承〜
abstract class session_data extends cgi_param {
//public:

public function __construct()
{
  $this->valid_time_ = 15 * 60;
  parent::__construct();
}

/**
 * セッションIDの設定
 *
 * @access public
 * @param string $id セッションID
 */
public function set_id($id) { $this->id_ = $id; }
/**
 * セッションIDの取得
 *
 * @access public
 * @return string セッションID
 */
public function get_id() { return $this->id_; }

/**
 * 有効期限(TTL)の設定
 *
 * 0または負の値を指定すると無期限とみなす
 * defaultは15分である
 *
 * @access public
 * @param int $t TTLの値を秒で
 */
public function set_validity_term($t) { $this->valid_time_ = $t; }

/**
 * 有効期限(TTL)の取得
 *
 * 0または負の値を指定すると無期限とみなす
 *
 * @access public
 * @return int TTLの値を秒で
 */
public function get_validity_term() { return $this->valid_time_; }

/**
 * 書き込み(Virtual)
 *
 * @access public
 * @return boolean 問題があればfalse
 */
abstract public function write();

/**
 * 読み込み(Virtual)
 *
 * @access public
 * @return boolean 問題があればfalse
 */
abstract public function read();

/**
 * 削除(Virtual)
 *
 * @access public
 * @return boolean 問題があればfalse
 */
abstract public function del();

/**
 * セッションIDの存在確認(Virtual)
 *
 * 書き込み先にすでにセッションIDが存在しているかの確認
 * 基本的に「trueが帰ってきたら上書きになりそうなので適宜対処」のイメージ
 *
 * @access public
 * @return boolean すでに存在していればtrue
 */
abstract public function is_session();

//private:
private $id_;
private $valid_time_; // 有効時間：単位は秒
} // end of class

