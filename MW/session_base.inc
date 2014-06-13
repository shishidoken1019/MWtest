<?php

/**
 * ���å��������Τδ��쥯�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class session_base {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->set_config(null);
  $this->set_error_string("");
}


/**
 * session config�Υ��å���
 *
 * @access public
 * @param session_config $o session_config���饹�Υ��󥹥���(�ؤλ���)
 */
public function set_config($o) { $this->config_obj_ = $o; }
protected function get_config() { return $this->config_obj_; }

//
public function set_db($o) { $this->dbh_ = $o; }
protected function get_db() { return $this->dbh_; }

//
protected function set_error_string($s) { $this->error_string_ = $s; }
public function get_error_string() { return $this->error_string_; }

//private:
private $config_obj_;
private $dbh_;
private $error_string_;

} // end of class
