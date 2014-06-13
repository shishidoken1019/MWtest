<?php

/**
 * バリデータ
 *
 * いわゆる「妥当性検証」を行う
 * 基本はインスタンス生成型だが、
 * chk メソッドだけはstaticに用いられる
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('is.inc');

/*
 チェックできるタイプはとりあえず以下を想定
any		種類問わず
alphanum	英数字
numeric		数値：minとmaxの意味合いが変わる
number          数字：minとmaxは文字数になるあたりがnumericとの差異
email
url
digit		数字
dir		ディレクトリ
date		日付

以下、未実装
alpha		英字
alpha_lower	英小文字
alpha_upper	英大文字
xdigit		16進数の数字
tel
jzip		日本の郵便番号

XXX 全角とかは使う人が実装してちょ(笑

 */

class validator {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->set_type("");
  $this->must_off();
  $this->set_min(-1);
  $this->set_max(-1);
  $this->clear_method();

  // 対応している各々のメソッドを列挙
  // XXX 増えたらここに追加〜
  // 英数字
  $this->push_method("alphanum", "is_alphanum");
  // 数値
  $this->push_method("numeric", "is_digit");
  // 数字
  $this->push_method("number", "is_digit");
  // 数字
  $this->push_method("digit", "is_digit");
  // email
  $this->push_method("email", "is_email");
  // url
  $this->push_method("url", "is_url");
  // dir
  $this->push_method("dir", "is_dir");
  // dir
  $this->push_method("date", "is_date");

  //
  $this->set_error_must(false);
  $this->set_error_type(false);
  $this->set_error_min(false);
  $this->set_error_max(false);

  //
  return;
}

////////////////////////
// アクセッサ
////////////////////////
//
public function set_type($s) { $this->type_ = $s; }
public function get_type() { return $this->type_; }
//
protected function set_must_flg($b) { $this->must_flg_ = $b; }
protected function get_must_flg() { return $this->must_flg_; }
//
public function must_on() { $this->set_must_flg(true); }
public function must_off() { $this->set_must_flg(false); }
public function is_must_flg() { return $this->get_must_flg(); }

//
public function set_min($i) { $this->min_ = $i; }
public function get_min() { return $this->min_; }

//
public function set_max($i) { $this->max_ = $i; }
public function get_max() { return $this->max_; }

//
public function push_method($n, $v) { $this->method_[$n] = $v; }
public function get_method($n)
{
  if (isset($this->method_[$n])) {
    return $this->method_[$n];
  } else {
    return "";
  }
}

public function clear_method() { $this->method_ = array(); }


//
protected function set_error($b) { $this->error_ = $b; }
protected function get_error() { return $this->error_; }
public function is_error() { return $this->error_; }
//
protected function set_error_must($b) { $this->error_must_ = $b; }
protected function get_error_must() { return $this->error_must_; }
public function is_error_must() { return $this->error_must_; }
//
protected function set_error_type($b) { $this->error_type_ = $b; }
protected function get_error_type() { return $this->error_type_; }
public function is_error_type() { return $this->error_type_; }
//
protected function set_error_min($b) { $this->error_min_ = $b; }
protected function get_error_min() { return $this->error_min_; }
public function is_error_min() { return $this->error_min_; }
//
protected function set_error_max($b) { $this->error_max_ = $b; }
protected function get_error_max() { return $this->error_max_; }
public function is_error_max() { return $this->error_max_; }


// -------------
// set_typeのラッパー各種
// -------------
public function set_type_alphanum() { $this->set_type('alphanum'); }
public function set_type_numeric() { $this->set_type('numeric'); }
public function set_type_email() { $this->set_type('email'); }
// 文字種別を問わない場合
public function set_type_any() { $this->set_type(''); }

////////////////////////
// メインロジック
////////////////////////

// チェックメソッド
// XXX staticなクラス
// OK ならtrue、だめならfalse
// bool chk($value, type, must_flg, min, max);
static public function chk($value, $type, $mflg = false, $min = -1, $max = -1)
{
  //
  $obj = new validator;
  $obj->set_type($type);
  if ($mflg) {
    $obj->must_on();
  } else {
    $obj->must_off();
  }
  $obj->set_min($min);
  $obj->set_max($max);

  //
  return $obj->check($value);
}

// チェックメソッド
// OK ならtrue、だめならfalse
public function check($value)
{
//print "validator value is $value \n";
  //
  $length = strlen($value);

  // まず必須チェック
  if (0 == $length) {
//print "length 0\n";
    // 必須項目ならエラーで突っ返す
    if ($this->is_must_flg()) {
      $this->set_error(true);
      $this->set_error_must(true);
//print "Trap 0.1\n";
//print "return false\n";
      return false;
    }
    // 必須じゃないなら、以下のチェック意味ないからOKで突っ返す
//print "Trap 0.2\n";
//print "return true\n";
    return true;
  }
//print "Trap 1\n";

  // 以降のためにその１
  $ret = true;

  // 次。タイプチェック
  $type = $this->get_type();
//print "type is $type \n";
  if ('any' !== $type) {
    if ("" !== $type) {
      $wk = $this->get_method($type);
      if ("" == $wk) {
        // XXX 設定がへん。どしよ？
        $this->set_error(true);
//print "invalid type\n";
//print "return false\n";
        return false;
      }

      // チェック
      if (false === is::$wk($value)) {
        // だめぽ
        $this->set_error(true);
        $this->set_error_type(true);
//print "type check ng. \n";
//print "return false\n";
        $ret = false;
      }
    }
  }

  // んで、lengthチェック
  if ("numeric" === $type) {
//print "into numeric \n";
    if (false === $this->get_error_type()) {
      if (-1 != $this->get_min()) {
        $value = $value + 0;
        if ($value < $this->get_min()) {
          // だめぽ
          $this->set_error(true);
          $this->set_error_min(true);
          $ret = false;
        }
      }
      if (-1 < $this->get_max()) {
        if ($value > $this->get_max()) {
          // だめぽ
          $this->set_error(true);
          $this->set_error_max(true);
          $ret = false;
        }
      }
    }
  } else {
//print "into no numeric\n";
//print "length = $length\n";
    // XXX
    if (-1 < $this->get_min()) {
//print "min check " . $this->get_min() . "\n";
      if ($length < $this->get_min()) {
//print "min check ng.\n";
        // だめぽ
        $this->set_error(true);
        $this->set_error_min(true);
        $ret = false;
      }
    }
    // XXX
    if (-1 < $this->get_max()) {
//print "max check " . $this->get_max() . "\n";
      if ($length > $this->get_max()) {
//print "min check ng.\n";
        // だめぽ
        $this->set_error(true);
        $this->set_error_max(true);
        $ret = false;
      }
    }
  }

  //
//var_dump($ret);
  return $ret;
}



//private:
private $type_;		// チェックタイプ
private $must_flg_;	// 必須フラグ：trueで必須
private $min_;		// 最小値。基本はbyteサイズだが、numericの場合は値
private $max_;		// 最大値。基本はbyteサイズだが、numericの場合は値
private $method_;	// メソッド名対応表
//
private $error_;	// とにかくerrorならtrue
private $error_must_;	// mustチェックでエラーならtrue
private $error_type_;	// typeチェックでエラーならtrue
private $error_min_;	// minチェックでエラーならtrue
private $error_max_;	// maxチェックでエラーならtrue


} // end of class

