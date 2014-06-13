<?php

/**
 * ファイル用ユーティリティクラス
 *
 * ファイル操作にまつわるユーティリティ系クラス
 * ユーティリティ系クラスなので、全て
 * file_util::メソッド
 * の形式でのcallを想定している
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

//
class file_util {

// ファイルパスを「拡張子と」「それ以外」に分解
// @return array [0]がそれ以外、[1]が拡張子(.付き) 拡張子はなければ空文字
static public function split_filename_by_extension($s)
{
$ret = -1;
$wk = 0;

  //
  while( false !== ($wk = strpos($s, '.', $wk))) {
    $ret = $wk;
    $wk ++;
  }

  //
  if (-1 !== $ret) {
    $a[] = substr($s, 0, $ret);
    $a[] = substr($s, $ret);
  } else {
    $a[] = $s;
    $a[] = '';
  }
//var_dump($a);

  //
  return $a;
}

// ファイル書き込み
// しくったらfalse
static public function add_file($filename, $data)
{
  $fp = @fopen($filename, "a");
  if(!$fp) {
//print "file open error!";
    return false;             // 終了
  }
  flock($fp, LOCK_EX);        // LOCK_EX => 排他ロック
  fwrite($fp, $data);
  fclose($fp);
  //
  return true;
}

// ファイル名からのファイルの読み込み
static public function read_file($filename)
{
$ret = "";
  //
  if ($fp = @fopen($filename, "r")) {
    // ファイルのopenに成功したら読み込む
    while (!feof($fp)) {
      $ret .= fgets($fp);
    }
    @fclose($fp);
  }
  //
  return $ret;
}

// ファイルを１行１データとして配列にとりこんでreturn
static public function read_file_to_array($filename)
{
  $awk = array();
  if ($fp = fopen($filename, 'r')) {
    while (!feof($fp)) {
      $awk[] = trim(fgets($fp));
    }
    fclose($fp);
  }
  //
  return $awk;
}

// ファイルを読み込んでEUC文字コードに変換してreturn
static public function read_file_to_euc($filename)
{
  return
    mb_convert_encoding(file_util::read_file($filename) , "EUC-JP", "auto");
}

// ファイルを読み込んでUTF-8文字コードに変換してreturn
static public function read_file_to_utf8($filename)
{
  return
    mb_convert_encoding(file_util::read_file($filename) , "UTF-8", "auto");
}

// ファイルを読み込んでbase64にしてreturn
static public function read_file_to_base64($filename)
{
  return base64_encode(file_util::read_file($filename));
}


} // end of class

