<?php
/**
 * �᡼���������饹
 *
 * �᡼�������Τ���Υ��饹���ºݤˤ�Virtual
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

abstract class mail_send {

//public:
public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
}

/**
 * �᡼��������Ԥ�
 *
 * @access public
 * @param internet_message_format_obj $mobj �᡼��ǡ�����ɽ�����󥹥���
 * @return boolean ���꤬ȯ��������false �ܺ٤��̥᥽�åɤǡ��Ĥ�ͽ�ꡣ
 */
abstract public function send(internet_message_format $mobj);

//private:

} // end of class