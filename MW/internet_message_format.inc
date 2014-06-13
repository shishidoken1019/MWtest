<?php

/**
 * Internet Message Formatを意味するクラス
 *
 * RFC2822準拠…予定のメールクラス(笑
 * 基本facadeだけど、面倒なのでheader_fieldsを継承してる
 * 文字エンコードが EUC -> jis で固定になってるので注意
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('internet_message_format_header_fields.inc');
require_once('internet_message_format_body_text.inc');
require_once('multibyte.inc');

class internet_message_format extends internet_message_format_header_fields {

public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}

//
public function init()
{
  parent::init();
  $this->set_envelope_from('');
  $this->envelope_to_ = array();
  //$this->verp_flg_off();
  // XXX 当面場当たり。後でfactory予定
  $this->internet_message_body_obj_ = new internet_message_format_body_text;
}

/**
 * envelope fromの設定
 *
 * わからなければ設定しないこと!!
 *
 * @access public
 * @param string $s envelope用のfromアドレス
 */
public function set_envelope_from($s) { $this->envelope_from_ = $s; }
// 表には出さないからDocument形式コメントは省略
public function get_envelope_from() { return $this->envelope_from_; }


/**
 * envelope toの設定
 *
 * わからなければ設定しないこと!!
 *
 * @access public
 * @param string $s envelope用のtoアドレス
 */
public function push_envelope_to($s) { $this->envelope_to_[] = $s; }
// 表には出さないからDocument形式コメントは省略
public function get_envelope_to() { return $this->envelope_to_; }

//
protected function get_body_obj() { return $this->internet_message_body_obj_; }

/**
 * mail bodyの設定
 *
 * @access public
 * @return string mailそのものをあらわす文字列。問題があれば空文字
 */
public function set_body($s)
  { $this->get_body_obj()->set_from_string($s); }

/**
 * mail stringの取得
 *
 * internet messageすべてを１本の文字列にして復帰
 *
 * @access public
 * @return string mailそのものをあらわす文字列。問題があれば空文字
 */
public function get_mail_string()
{
$ret = "";
  // まずヘッダの取り出し
  $ret = $this->get_all_headers();
  $ret .= "\r\n";

  // XXX いったんiso-2022jp固定
  // XXX しかも内部エンコードeuc固定
  $m = new multibyte;
  $m->set_jis();
  $m->set_from_encoding_euc();
  $ret .= $m->convert($this->get_body_obj()->get_to_string());
//var_dump($this->get_body_obj()->get_to_string());
//var_dump($ret);

  //
  return $ret;
}

//
//public function set_mail_string($s) : parse


//private:
private $envelope_from_;
private $envelope_to_;
//private $verp_flg_;
private $internet_message_body_obj_;

} // end of class

