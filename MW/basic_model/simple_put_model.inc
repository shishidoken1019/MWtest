<?php

/**
 * ñ��ʽ�����model
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */
require_once('base_model.inc');

class simple_put_model extends base_model {

//
public function initialize() {  }
public function finalize() {  }

//����
public function execute() {
  ///////////////////////////////
  // ���Ͻ���
  ///////////////////////////////
  $this->make_body_with_conv();
}

} // end of class