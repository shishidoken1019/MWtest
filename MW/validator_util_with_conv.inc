<?php

/**
 * バリデータ util
 * convと結びつけて楽々エラー画面セット
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('conv_util.inc');

/*
テンプレート条件

name="hoge" value=%%%hoge%%%

$$$if_error_hoge$$$
とにかくエラーざます
$$$/if_error_hoge$$$


$$$if_error_must_hoge$$$
hogeがないyo 必須だよをい
$$$/if_error_must_hoge$$$

$$$if_error_type_hoge$$$
typeが違げぇよ本来なら %%%valid_type_hoge%%%なはずだろ？
$$$/if_error_type_hoge$$$

$$$if_error_min_hoge$$$
ちっちゃすぎるから！！
最低でも %%%valid_min_hoge%%%くらいは欲しいから！！
$$$/if_error_min_hoge$$$

$$$if_error_max_hoge$$$
でけぇよをい
なんぼなんでも %%%if_error_max_hoge%%%こえたら行き過ぎだろをい
$$$/if_error_max_hoge$$$

 */

require_once('validator_util.inc');

class validator_util_with_conv extends validator_util {

public function __construct()
{
  //
  parent::__construct();
  // 
  //$this->init();
}

//
public function init()
{
  parent::init();
}

// アクセッサ
public function set_conv($o) { $this->conv_ = $o; }
public function get_conv() { return $this->conv_; }

// XXX 廃止予定
public function set_all_datas()
{
  $conv = $this->get_conv();
  $values = $this->make_all_datas();
  $so = new simple_put;
  foreach ($values as $key => $value) {
    if ($value === true) {
      $conv->multiDic($key, $so);
    } else
    if ($value === false) {
      // ここはなにも設定しない〜
      ;
    } else {
      // 入力データの保持
      // 単体用
      $conv->monoDic($key, $value);
      // checked 用
      conv_util::monoDicChecked($conv, 'checked_' . $key, $value);
      // selected 用
      conv_util::monoDicSelected($conv, 'selected_' . $key, $value);
    }
  }
}

//
public function is_valid()
{
  $ret = parent::is_valid();
//print "with conv ret is ";
//var_dump($ret);
  $conv = $this->get_conv();
  $values = $this->get_value_set_as_a_template();
  $so = new simple_put;
//var_dump($values);

  // エラー表示周りのみ
  if (false === empty($values) ) {
    foreach ($values as $key => $value) {
      if ($value === true) {
//print "$key is true<br>\n";
        $conv->multiDic($key, $so);
      }
    }
  }
  //
  return $ret;
}


//private:
private $conv_;	// convインスタンス

} // end of class

