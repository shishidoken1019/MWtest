<?php

/**
 * ��ʸ�����饹 : Text_Pictogram_Mobile�⥸�塼���ѥ����ץ�
 *
 * http://blog.asial.co.jp/380
 * http://blog.asial.co.jp/351
 * ����
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('Text/Pictogram/Mobile.php');

class emoji_adapter_Text_Pictogram_Mobile {

/**
 * ���󥹥��󥹼��
 *
 * @access public
 * @param mobile_info_obj $mobj mobile_info���󥹥���
 * @param string $type ʸ�������ɡ����� sjis �Τ�
 * @return Text_Pictogram_Mobile�ϥ��󥹥��� ���꤬������null
 */
static public function get_obj(mobile_info $mobj, $type = 'sjis')
{
  //
  $carrier = 'docomo'; // �ǥե��ϤȤꤢ����DoCoMo
  if (true === $mobj->is_ez()) {
    $carrier = 'ezweb';
  } else
  if (true === $mobj->is_softbank()) {
    $carrier = 'softbank';
  }

/*
  //
  $t = mb_detect_encoding($s, 'sjis-win,UTF-8,eucjp-win,JIS,ASCII');
  // �Ȥꤢ�������˥����å�
  $type = 'sjis';
  if ($t === 'UTF-8') {
    $type = 'utf-8';
  }
print "type is $type <br />\n"
*/

  //
  $pobj = Text_Pictogram_Mobile::factory($carrier, $type);
  $pobj->setIntercodePrefix('[emoji');
  $pobj->setIntercodeSuffix(']');

  //
  return $pobj;
}


//private:

} // end of class
