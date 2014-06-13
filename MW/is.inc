<?php

/**
 * ISクラス
 *
 * 様々な文字列判定用クラス
 * 基本的に is::メソッド名 で使うこと
 * XXX とりあえず正規表現。重いからそのうち改修したいなぁ
 * XXX 正規表現自体も、POSIX Regex と Perl Regex と混ざってるし…
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

// is_date用
require_once('calendar.inc');

class is
{


/**
 * is_alphanum
 *
 */
static public function is_alphanum($s){
/*
  if (ereg ("[^0-9a-zA-Z]", $s)) {
    return false;
  }
  return true;
*/
  return ctype_alnum($s);
}


/**
 * is_digit
 *
 */
static public function is_digit($num){
/*
  if (ereg ("[^0-9]", $num)) {
    return false;
  }
  return true;
*/
  return ctype_digit($num);
}

  /**
   * is_kana
   *
   */
  static public function is_kana($str){
    if(!ereg( "^(\xA5[\xA1-\xF6]|\xA1\xBC|\xA1\xA6|\xA1\xA1|\x20)+$", $str)){
      return false;
    }
    return true;
  }

  /**
   * is_email 
   *
   *
   */
  static public function is_email ($mail) {
    if (!ereg ("[0-9a-zA-Z\.\-]@[0-9a-zA-Z\.\-]", $mail)) {
      return false;
    } else {
      // ドメイン部分のチェック
      $domain = ereg_replace ("[^@]*@", "", $mail);
      if (ereg ("[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}", $domain)) {
        // ドメイン部分がIPアドレスだった場合の処理
        $ip = explode (".", $domain);
        for ($i = 0; $i < 4; $i++) {
          if (strlen($ip[$i]) == 0 || $ip[$i] > 255) {
            $x = "error";
            break;
          }
        }
        if ($x) {
          return false;
        }
      // IPでない場合のドメインチェック
      }else if(is::is_domain($domain)){
        // ドメイン部の文字数チェック
        if(255 < strlen($domain)){
          return false;
        }
      }else{
        return false;
      }
      // ローカル部分のチェック
      $local = substr($mail,0,strrpos($mail,"@".$domain));
      // ローカル部の文字数チェック
      if(64 < strlen($local)){
        return false;
      }
      // スクリプト等を禁止するために＜＞は禁止！する！！
      if(ereg("<|>",$local)){
        return false;
      }
    }
    return true;
  }

  /**
   * is_domain
   *
   *
   */
  static public function is_domain($domain){
    //$chars = "((([a-zA-Z0-9])|([a-zA-Z0-9])(([a-zA-Z0-9])|-)*([a-zA-Z0-9])))*(([a-zA-Z])|([a-zA-Z])(([a-zA-Z0-9])|-)*([a-zA-Z0-9]))+\.?";
    $chars = "(^[0-9a-zA-Z]+[0-9a-zA-Z\-]*[0-9a-zA-Z]{1}\.{0,1})*[0-9a-zA-Z]{1}$";
    if(!ereg($chars, $domain)){
      return false;
    }
    return true;
  }

  //
  static public function is_url($url){
    if (preg_match('/^(https?|ftp)(:\/\/[-_.!~*\'()a-zA-Z0-9;\/?:\@&=+\$,%#]+)$/
', $url)) {
      return true;
    }
    // else 
    return false;
  }

/**
 * is_dir
 * ディレクトリ名
 * XXX 当面、英数字＋_-を有効とする
 *
 */
static function is_dir($s) {
  if (preg_match("/[^0-9a-zA-Z\-_]+/", $s)) {
    return false;
  }
  return true;
}

/**
 * 日付
 *
 */
static function is_date($s) {
  $cal = new calendar;
  $cal->set_string($s);

  //
  return $cal->is();
}

// XXX
// 引数が全角カタカナのみで構成されていれば真
// ただし、文字コードの設定がされている必要があります。
// ▼例
// mb_regex_encoding('euc-jp');
public static function is_katakana($s) {
mb_regex_encoding('euc-jp');
  $ret = mb_ereg("^[アイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワヲンガギグゲゴザジズゼゾダヂヅデドバビブベボパポピプペポァィゥェォッャュョー]*$", $s);
  // XXX 暫定なのでとりあえずざっくり
  if (false === $ret) {
    return false;
  }
  // else
  return true;
}

// is_zip
public function is_zip($s)
{
  if (preg_match("/^[0-9][0-9][0-9][\- ]?[0-9][0-9][0-9][0-9]$/", $s)) {
    return true;
  }
  // else
  return false;
}

// is_zip2
public function is_zip2($s1, $s2)
{
  if (3 !== strlen($s1)) {
    return false;
  }
  if (4 !== strlen($s2)) {
    return false;
  }
  // XXX まとめて
  return is::is_digit($s1)&&is::is_digit($s2);
}


// is_tel
public function is_tel($s)
{
  if (preg_match("/^0[0-9]{1,4}[\- ]?[0-9]{1,4}[\- ]?[0-9]{4}$/", $s)) {
    return true;
  }
  // else
  return false;
}

// is_tel3



} // end of class
