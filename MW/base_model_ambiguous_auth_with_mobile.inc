<?php

/**
 * ���Ӹ����������б��� MVC Model��ʬǧ�ڷϴ��쥯�饹
 * 
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model_rich.inc');

abstract class base_model_ambiguous_auth_with_mobile extends base_model_rich {

//public:
public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}


//�����
public function init(){
  parent::init();
  $this->set_authtype_ambiguous_auth();
  $this->with_mobile_on();
}

//
abstract public function execute_ambiguous_auth();

} // end of class
