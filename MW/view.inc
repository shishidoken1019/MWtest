<?php

/**
 * Viewクラス
 *
 * 基本的には出力して終わり
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('file_util.inc');

class view {

//
public function __construct() { $this->init(); }

//
public function init() { }

public function set_body($s) { $this->body_ = $s; }
// XXX
public function get_body() {
 if ("" != $this->body_) {
   return $this->body_;
  }
  // else
  return $this->get_body_from_convert();
}

public function set_res_obj($o) { $this->res_obj_ = $o; }
public function get_res_obj() { return $this->res_obj_; }

public function set_multi_obj($o) { $this->multi_obj_ = $o; }
public function get_multi_obj() { return $this->multi_obj_; }

public function set_model_obj($o) { $this->model_obj_ = $o; }
public function get_model_obj() { return $this->model_obj_; }

public function get_template_string()
{
  //
  $tf = $this->get_template_filename();
  return file_util::read_file($tf);
}

public function get_template_filename()
{
  // 必要なインスタンスげと
  $mobj = $this->get_model_obj();
//var_dump($mobj);

  // テンプレートファイルのfullディレクトリ作成
//var_dump($mobj);
//var_dump($mobj->get_tmp_filename());
//var_dump($tf);
  $tf = $mobj->get_config()->find('template_dir') . $mobj->get_tmp_filename();

  // ファイルが存在しなければはじく
  if (false === is_file($tf)) {
    throw new Exception("template file not find!!");
  }

  //
  return $tf;
}


// bodyが空のときにmodelからごりごり作成
// エラーなら空文字
public function get_body_from_convert()
{
//print "get_body_from_convert \n";
  // 必要なインスタンスげと
  $mobj = $this->get_model_obj();
  $incode = $mobj->get_inside_encoding_obj();
  // XXX 微妙に怖いなぁここ…
  $incode->set_from_encoding_unknown();
  // convインスタンスげと
  // …conv固定もどんなもんかねぇ
  $conv = $mobj->get_conv();

  $cn = get_class($conv);
  if (false === (stristr($cn, 'smarty'))) {
    // テンプレートファイルを文字列として取得
    $ts = $this->get_template_string();
    //
    $out = $conv->conv($incode->convert($ts));
  } else {
    // テンプレートファイル名を取得
    $fn = $this->get_template_filename();
    // smarty的処理
    $out = $conv->fetch($fn);
  }

  //
  return $out;
}

//
public function put_contents_header()
{
  //
  $res = $this->get_res_obj();
//var_dump($res);
  // ヘッダの出力
  $res->set_nocache();
  $res->put();
}

public function get_contents_body()
{
  //
  $res = $this->get_res_obj();
  $mobj = $this->get_multi_obj();

  // bodyの出力
  if ($res->is_need_convert()) {
    // 文字系っぽいので置換して出力〜
    return $mobj->convert( $this->get_body() );
  }
  // else
  // 文字コード置換必要なさそうなのでそのまま〜
  return $this->get_body();
}

//
public function output()
{
  // まず作成
  //print $this->get_contents_body();
  $out = $this->get_contents_body();
  if ("" === $out) {
    throw new Exception("body is empty!!");
  }
  //
  $out = $this->output_extra($out);

  // ヘッダ出力
  $this->put_contents_header();

  // body出力
  // echoが早いとか言う話なので…まぁ一応
  //print $out;
  echo $out;

  //
  return true;
}

// 出力直前での処理：置換とか全部終わった後
// 特別な処理をするときはここに上書いて
public function output_extra($s) {
  return $s;
}


//private:
private $body_;
private $res_obj_;
private $multi_obj_;
private $model_obj_; // XXX 場当たり？

} // end of class

