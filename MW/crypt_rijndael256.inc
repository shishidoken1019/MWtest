<?php
require_once('crypt_base.inc');
require_once('block_cipher_mode_util.inc');

/*
 * メモ
 * 変数名の使い分け
 * encrypted_unit = 暗号化された文字列（IV含む）
 * encrypted_text = 暗号化された文字列（IV含まない）
 */

class crypt_rijndael256 extends crypt_base {

/*
 * コンストラクタ
 */
public function __construct() {
  $this->init();
}

/*
 * 初期化
 */
public function init() {
  parent::init();
  $this->set_plain_text("");
  $this->set_encrypted_unit("");
  $this->set_key("");
  $this->set_block_mode("");
}


/*
 * セッター／ゲッター
 */
// 平文
public function set_plain_text($s){
  $this->plain_text_ = $s;
}
public function get_plain_text(){
  return $this->plain_text_;
}
// 暗号化された文字列(IV含む)
public function set_encrypted_unit($s){
  $this->encrypted_unit_ = $s;
}
public function get_encrypted_unit(){
  return $this->encrypted_unit_;
}
// 暗号キー
public function set_key($s){
  $this->key_ = $s;
}
public function get_key(){
  return $this->key_;
}
// ブロックモード
public function set_block_mode($s){
  $this->block_mode_ = $s;
}
public function get_block_mode(){
  return $this->block_mode_;
}

/*
 * 暗号化
 */
public function encrypt() {
  $this->crypt("en");
}

/*
 * 複合化
 */
public function decrypt() {
  $this->crypt("de");
}

// 実処理
private function crypt($type) {
//print "crypt Trap 1\n";
  // IV を付加した文字列管理クラス作成
  $eu_o = new block_cipher_mode_util;

  // 暗号鍵を取得
//print "crypt Trap 2\n";
  $key = $this->get_key();
  // 暗号処理のモードを取得
  $block_mode = $this->get_block_mode();

//print "crypt Trap 3\n";
  if($type == "en") {
//print "crypt Trap 4\n";
    $plain_text = $this->get_plain_text();
  }
  else {
    $encrypted_unit = $this->get_encrypted_unit();
    $eu_o->set_encrypted_unit($encrypted_unit);
    $eu_o->split();
    $encrypted_text = $eu_o->get_encrypted_text();
    $iv = $eu_o->get_iv();
  }

//print "crypt Trap 5\n";
  $td = mcrypt_module_open('rijndael-256', '', $block_mode, '');

  // IV取得
  if($type == "en") {
//print "crypt Trap 6\n";
    $iv_size = mcrypt_enc_get_iv_size($td);
//print "crypt Trap 6-1\n";
    // XXX
    //$iv = mcrypt_create_iv($iv_size, MCRYPT_DEV_RANDOM);
    //srand();
    //$iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
    $iv = mcrypt_create_iv($iv_size, MCRYPT_DEV_URANDOM);
//print "crypt Trap 6-2\n";
  }
  else{
    $iv = $eu_o->get_iv();
  }

  // 暗号キーのサイズを取得
//print "crypt Trap 7\n";
  $ks = mcrypt_enc_get_key_size($td);

  // 暗号キー作成
//print "crypt Trap 8\n";
  $md5_key = substr(md5($key), 0, $ks);

  // 初期化
//print "crypt Trap 9\n";
  $ret = @mcrypt_generic_init($td, $md5_key, $iv);
//var_dump($ret);
  if (false === $ret) {
    return false;
  }

  /* 暗号化処理を初期化します */
  if($type == "en") {
    $encrypted = mcrypt_generic($td, $plain_text);
  }
  else {
    $decrypted_text = rtrim(@mdecrypt_generic($td, $encrypted_text));  // データパディングされるので
  }

  /* 暗号化ハンドラを終了します */
  mcrypt_generic_deinit($td);
  mcrypt_module_close($td);

  if($type == "en") {
    // IV を付加した文字列を結合
    $eu_o->set_encrypted_text($encrypted);
    $eu_o->set_iv($iv);
    $eu_o->set_iv_size($iv_size);
    $eu_o->combine();
    $unit = $eu_o->get_encrypted_unit();
  
    $this->set_encrypted_unit($unit);
  }
  else {
    $this->set_plain_text($decrypted_text);
  }
  //
  return true;
}

// private:
// 暗号化したい文字列
private $plain_text_;

// 暗号キー
private $key_;

// 暗号化した文字列(IV含む)
private $encrypted_unit_;

// ブロックモード
private $block_mode_;

}

