<?php

/**
 * emoji_base��Ϣ�ʤ륯�饹�Υե����ȥ꡼
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('emoji_docomo.inc');
require_once('emoji_ez.inc');
require_once('emoji_softbank_binary.inc');

class emoji_factory {

/**
 * ����˹�碌�����֥������Ȥ�return
 *
 * @access public��private��protected��
 * @param string $type �������docomo��ez��softbank�Τ����줫(���Ȥ��ѹ�
 * @return emoji_base_obj ɬ�פʥ��󥹥��󥹡����顼�ʤ�null
 */
static public function get_instance($type)
{
  $o = null;

  if (0 === strcasecmp($type, 'docomo')) {
    $o = new emoji_docomo;
  } else
  if (0 === strcasecmp($type, 'au')) {
    $o = new emoji_ez;
  } else
  if (0 === strcasecmp($type, 'ez')) {
    $o = new emoji_ez;
  } else
  if (0 === strcasecmp($type, 'softbank')) {
    $o = new emoji_softbank_binary;
  }
  //
  return $o;
}


} // end of class
