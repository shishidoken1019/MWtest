<?php

/**
 * securityクラス
 *
 * 基本はサニタイズ＆チェック
 *
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

class security
{

// HTML用(XSS対抗)サニタイズ
static public function sanitize_html($base_string)
{
  // XXX とりあえずhtmlsppuecialchars 使うけど問題あったら速攻自作!!
  // XXX htmlentitiesは適用範囲がもう一つ不明なので怖いから使わん
  // XXX シングルクォートもエスケープしておきたいので ENT_QUOTES を add
  return htmlspecialchars($base_string, ENT_QUOTES);
}


//正規表現用のサニタイズ
static public function sanitize_regex($base_string)
{
  $ret = "";
  // XXX 数字のみの時にint扱いされないように。…カンベンしてくれ；；
  $base_string = $base_string . "";

  $length = strlen($base_string);
  for($i = 0; $i < $length; $i ++) {
    $itr = $base_string[$i];
    switch($itr) {
      // 以下の文字は '\'でエスケープしておく
      case '#':
      case '/':
      case '?':
      case '*':
      case '+':
      case '^':
      case '$':
      case '.':
      case '[':
      case ']':
      case '|':
      case '(':
      case ')':
      case '{':
      case '}':
      case '-':
      case '\\':
        $ret .= '\\';
        break;

      default:
        break;
    }
    $ret .= $itr;
  }
  //
  return $ret;
}

// DB用のサニタイズ
static public function sanitize_db($base_string)
{
  // XXX addslashes はバグってるので使わない!!
  // return addslashes($base_string);

  // 実装
$ret = "";
  // XXX 数字のみの時にint扱いされないように。…カンベンしてくれ；；
  $base_string = $base_string . "";
  $length = strlen($base_string);
  for($i = 0; $i < $length; $i ++) {
    $itr = $base_string[$i];
    switch($itr) {
      // 以下の文字は '\'でエスケープしておく
      case '\'':
      case ';':
      case '"':
      case '\\':
        $ret .= '\\';
        break;


      default:
        break;
    }
    $ret .= $itr;
  }

  //
  return $ret;
}

// お便利用
static public function sanitize_db_add_quote($base_string, $quote_string = "'")
{
  // まずサニタイズ
  $ret = security::sanitize_db($base_string);

  // クォートをつける
  if($ret === '')
	  return "null";
  else
	  return $quote_string . $ret . $quote_string;
  
}

// header Injection用
// XXX とりあえず単純にCRLFを削除
static public function sanitize_header_fields_data($base_string)
{
  $ret = preg_replace('/[\r\n]/', '', $base_string);
  return $ret;
}

} // end of class

