<?php

/**
 * バリデータ data_clumpとcgiとを結びつけるクラス
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('validator.inc');

class validator_clump_unit extends validator {

public function __construct()
{
  //
  parent::__construct();
  // parentでも叩くので省略
  //$this->init();
}

//
public function init()
{
  //
  parent::init();
  //
  $this->set_cgi_name("");
  //$this->set_clump_name("");
}

// アクセッサ
public function set_cgi_name($s) { $this->cgi_name_ = $s; }
public function get_cgi_name() { return $this->cgi_name_; }

/*
//
public function set_clump_name($s) { $this->clump_name_ = $s; }
public function get_clump_name() { return $this->clump_name_; }
*/


//private:
//private $clump_name_;	// data_clumpの定義名
private $cgi_name_;	// cgi(form)の定義名

} // end of class

