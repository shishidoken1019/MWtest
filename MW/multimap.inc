<?php

/**
 *
 * multimapクラス
 *
 * キーの重複を許すmap(ようはハッシュ配列だ)
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Kohei Yamada <hecomark@gmail.com>
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

// 2005/2/24 イテレータは単に配列の添字なので、
//           中身を参照する場合は$ob->real($itr)のように
//           使用してください。
//           要素は基本的にPairオブジェクトなので、
//           $key = $ob->real($itr)->get_first();
//           $value = $ob->real($itr)->get_second();
//           のように参照します。
//
 
require_once("pair.inc");
 
class multimap
{

public function __construct()
{
  $this->init();
}

public function init()
{
  $this->data_ = array();
}

/**
 * begin
 *
 * 最初の要素を指すイテレータを返す
 *
 * @param 引数の説明。
 * @return  戻り値の説明
 * @access public
 * @since 1.0
 */
public function begin()
{
  // 今のところは配列の添字を返す
  // いちおうイテレータ扱い
  return 0;
}

/**
 * end
 *
 * 最後の要素の次を指すイテレータを返す
 * XXX 最後の要素の「次」である点に注意
 *
 */
public function end()
{
  return $this->size();
}

/**
 * rbegin
 *
 * 先頭の要素を指す逆イテレータを返す。
 *
 */
public function rbegin()
{
  // 配列の添字になるので+1
  return abs(-($this->size()) + 1);
}

/**
 * rend
 *
 * 最後の要素を指すイテレータを返す
 *
 */
public function rend()
{
  // 最後の次の要素を指すように+1
  return 0 + 1;
}

/**
 * insert
 *
 * （今の所先頭に）$key, $valueのPairオブジェクトを追加する
 * 戻り値は挿入した要素を指すイテレータ
 *
 * @param $key=キー, $value=値
 * @return  挿入された位置を示すイテレータを返す
 * @access public
 * @since 1.0
 */
public function insert($key, $value)
{
  // とりあえず最低限の動き

  $obj = new pair();
  $obj->set($key, $value);
  $this->data_[] = $obj;

  // 常に最後尾に入るはずなので
  return $this->size() - 1;  
}

/**
 * find
 *
 * $keyをキーに持つ最初の要素を探して、
 * その要素を指すイテレータを返す。
 * iterator自体は数値…ってのはPHP時の制約
 * キーが見つからない場合はnull(中に何が入ってるかわからないから
 *
 */
public function find($key)
{
  $ret = $this->find_array($key);

  // 微妙ご法度な関数だが、配列限定なので
  if (empty($ret)) {
    return null; 
  }
  //
  return $ret[0];
}

/**
 * find_array
 *
 * $keyをキーに持つ最初の要素を探して、
 * その要素を指すイテレータを返す。
 * キーが見つからない場合は空配列を返す
 *
 */
public function find_array($key)
{
  $ret = array();
  //
  for($itr = $this->begin(); $itr != $this->end(); $itr++){
    if(strcmp($this->real($itr)->get_first(), $key)==0){
      $ret[] = $itr;
    }
  }

  //
  return $ret; 
}

//*******************************//

/**
 * isempty
 *
 * 空だとtrue
 *
 * @param 引数の説明。
 * @return  戻り値の説明
 * @access public
 * @since 1.0
 */
public function isempty()
{
  return empty($this->data_); 
}

/**
 * size
 *
 * 全ての要素の数を返す
 *
 * @param 引数の説明。
 * @return  戻り値の説明
 * @access public
 * @since 1.0
 */
public function size()
{
  return count($this->data_);
}

/**
 * erase
 *
 * firstの要素を削除する。
 * あるいは、firstからlastまでの要素を削除する
 *
 * @param first=削除する要素の最初を指すイテレータ
 *        last =削除する要素の最後の次を指すイテレータ
 * @return  削除した要素の次を指すイテレータ
 * @access public
 * @since 1.0
 */
public function erase($first, $last = false)
{
  if(false !== $last){
    // last指定があれば、first,lastの間の要素を削除
    array_splice($this->data_, $first, $last-$first);
  }else{
    array_splice($this->data_, $first, 1);
  }
  
  return $first;
}

/**
 * clear
 *
 * 全ての要素を削除
 *
 */
public function clear()
{
  $this->data_ = array();
}

/**
 * real
 *
 * イテレータの指す要素のオブジェクトを返す（ポインタもどき）
 * $itrが負の値の場合はエラー処理。とりあえず空文字かえす。
 *
 * @param 引数の説明。
 * @return  戻り値の説明
 * @access public
 * @since 1.0
 */
public function real($itr)
{
  if($itr < 0){
    return "";
  }

  return $this->data_[$itr];
}

/*
 * 要素を足しこむ
 *
 */
public function add(multimap $o)
{
  for($itr = $o->begin(); $itr != $o->end(); $itr ++) {
    $this->insert($o->real($itr)->get_first(), $o->real($itr)->get_second());
  }
  return true;
}

/**
 * キー一覧取得
 */
public function get_all_keys()
{
  // とりあえず雑にげと
  $names = array();
  for($itr = $this->begin(); $itr != $this->end(); $itr ++) {
    // 文字列合成
    $names[$this->real($itr)->get_first()] = 1;
  }

  $keys = array_keys($names);
  return $keys;
}

/**
 * 指定されたkeyを持つ要素を削除する。
 *
 * keyが空文字の場合「なにもしない」
 * 全削除したいならclearメソッドつかって。
 *
 * @access public
 * @param string $key 削除したいkey文字列
 * @return integer 削除した要素数
 */
public function erase_key($key)
{
  //
  if ("" === $key) {
    return 0;
  }

  // 対象を検索 & 削除
  $ret = 0;
  while(false === is_null($itr = $this->find($key))) {
    // 削除対象数取得
    $ret ++;
    $this->erase($itr);
  }
//var_dump($this->data_);

  //
  return $ret;
}


//
private $data_;
} // end of class


