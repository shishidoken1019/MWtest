<?php

/**
 * ñ��ʽ�����model ǧ�ڷ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */


require_once('base_model_auth.inc');

class simple_put_model_auth extends base_model_auth {

//
public function initialize() {  }
public function finalize() {  }

//����
public function execute_auth() {
  ///////////////////////////////
  // ���Ͻ���
  ///////////////////////////////
  $this->make_body_with_conv();
}

} // end of class