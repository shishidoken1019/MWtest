<?php

/**
 * data_clumpにvalidator機能を添付させたもの
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('data_clump.inc');
require_once("validator_clump_unit.inc");

class data_clump_validator extends data_clump {

public function __construct() { parent::__construct(); }
public function init() { parent::init(); }

// 指定された引数のnameに対応するvalidator インスタンス配列を復帰
public function get_validate_obj($lists) {
  $ret = array();
  foreach($lists as $name) {
    if (isset($this->validate_objs_[$name])) {
      //$ret[] = $this->validate_objs_[$name];
      $ret[$name] = $this->validate_objs_[$name];
    }
  }
  return $ret;
}

public function make_validate($name, $type, $must = false, $min = -1, $max = -1) {
  $obj = new validator_clump_unit;
  //$obj->set_cgi_name($name);
  $obj->set_cgi_name($this->get_cgi_name($name));
  $obj->set_type($type);
  if ($must) {
    $obj->must_on();
  } else {
    $obj->must_off();
  }
  $obj->set_min($min);
  $obj->set_max($max);
  //
  $this->validate_objs_[$name] = $obj;
}

//
private $validate_objs_ = array();
} // end of class

