<?php

/**
 * ³¨Ê¸»ú¥¯¥é¥¹ : Text_Pictogram_Mobile¥â¥¸¥å¡¼¥ëÍÑ¥¢¥À¥×¥¿
 *
 * http://blog.asial.co.jp/380
 * http://blog.asial.co.jp/351
 * »²¾È
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
 * ¥¤¥ó¥¹¥¿¥ó¥¹¼èÆ
 *
 * @access public
 * @param mobile_info_obj $mobj mobile_info¥¤¥ó¥¹¥¿¥ó¥¹
 * @param string $type Ê¸»ú¥³¡¼¥É¡§ÅöÌÌ sjis ¤Î¤ß
 * @return Text_Pictogram_Mobile·Ï¥¤¥ó¥¹¥¿¥ó¥¹ ÌäÂê¤¬¤¢¤ë¾ì¹çnull
 */
static public function get_obj(mobile_info $mobj, $type = 'sjis')
{
  //
  $carrier = 'docomo'; // ¥Ç¥Õ¥©¤Ï¤È¤ê¤¢¤¨¤ºDoCoMo
  if (true === $mobj->is_ez()) {
    $carrier = 'ezweb';
  } else
  if (true === $mobj->is_softbank()) {
    $carrier = 'softbank';
  }

/*
  //
  $t = mb_detect_encoding($s, 'sjis-win,UTF-8,eucjp-win,JIS,ASCII');
  // ¤È¤ê¤¢¤¨¤º»¨¤Ë¥¹¥¤¥Ã¥Á
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

