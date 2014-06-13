<?php

/**
 * ペアクラス
 *
 * ２つの要素を持つ単純なクラス
 * 概ね、各コンテナークラス用の下っ端
 *
 * @package magicweapon
 * @access  public
 * @author  Kohei Yamada <hecomark@gmail.com>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

class pair
{
//public:
function __construct()
{
  $this->init();
}

function init()
{
  unset($this->first_);
  unset($this->second_);
}

function get_first() { return $this->first_; }
function get_second() { return $this->second_; }
function set_first($x) { $this->first_ = $x; }
function set_second($x) { $this->second_ = $x; }

function set($fir, $sec) { $this->set_first($fir); $this->set_second($sec); }

//private:
private $first_;
private $second_;

} // end of class

