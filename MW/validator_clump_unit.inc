<?php

/**
 * �Х�ǡ��� data_clump��cgi�Ȥ��ӤĤ��륯�饹
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
  // parent�Ǥ�á���ΤǾ�ά
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

// �������å�
public function set_cgi_name($s) { $this->cgi_name_ = $s; }
public function get_cgi_name() { return $this->cgi_name_; }

/*
//
public function set_clump_name($s) { $this->clump_name_ = $s; }
public function get_clump_name() { return $this->clump_name_; }
*/


//private:
//private $clump_name_;	// data_clump�����̾
private $cgi_name_;	// cgi(form)�����̾

} // end of class
