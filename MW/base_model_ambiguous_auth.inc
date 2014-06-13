<?php

/**
 * MVC Model��ʬǧ�ڷϴ��쥯�饹
 *
 * ���Υ��饹�ϡ�ǧ�ڤ��ƤƤ⤷�Ƥʤ��Ƥ�ɤä��Ǥ�ok�פʻ��˻��ѡ�
 * session.inc����ˤ���session���饹����Ȥ����Ȥ�����ˤ���������class
 * auth�ϥ��饹�δ���Ȥ��ƻȤ����Ȥ�����ˤ��Ƥ��롣
 * ����ե�����Ŭ�ڤ����ꤹ��С��ۤܤ��Τޤ޻Ȥ���Ȥ��⤦��
 * ̵���ʤ�Ŭ�����ľ���ʤ�Ѿ�����ʤꤷ�Ƥ��硣
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model_rich.inc');

abstract class base_model_ambiguous_auth extends base_model_rich {

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
  $this->with_mobile_off();
}

abstract public function execute_ambiguous_auth();

} // end of class
