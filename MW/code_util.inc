<?php

/**
 * ¥³¡¼¥É·Ï¥æ¡¼¥Æ¥£¥ê¥Æ¥£
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/


class code_util {

/**
 * ÅÔÆ»ÉÜ¸©¼èÆÀ
 *
 * @access public
 * @param int $i ÅÔÆ»ÉÜ¸©¥³¡¼¥É
 * @return string ¥³¡¼¥É¤Ë¤¢¤Ã¤¿ÃÍ ÌäÂê¤¬¤¢¤ì¤Ð¶õÊ¸»ú
 */
static public function prefecture($i)
{
  if (1 > $i) { return ""; }
  if (47 < $i) { return ""; }

  //
  $area_val = array(
    '1' => 'ËÌ³¤Æ»',
    '2' => 'ÀÄ¿¹¸©',
    '3' => '´ä¼ê¸©',
    '4' => 'µÜ¾ë¸©',
    '5' => '½©ÅÄ¸©',
    '6' => '»³·Á¸©',
    '7' => 'Ê¡Åç¸©',
    '8' => '°ñ¾ë¸©',
    '9' => 'ÆÊÌÚ¸©',
    '10' => '·²ÇÏ¸©',
    '11' => 'ºë¶Ì¸©',
    '12' => 'ÀéÍÕ¸©',
    '13' => 'ÅìµþÅÔ',
    '14' => '¿ÀÆàÀî¸©',
    '15' => '¿·³ã¸©',
    '16' => 'ÉÙ»³¸©',
    '17' => 'ÀÐÀî¸©',
    '18' => 'Ê¡°æ¸©',
    '19' => '»³Íü¸©',
    '20' => 'Ä¹Ìî¸©',
    '21' => '´ôÉì¸©',
    '22' => 'ÀÅ²¬¸©',
    '23' => '°¦ÃÎ¸©',
    '24' => '»°½Å¸©',
    '25' => '¼¢²ì¸©',
    '26' => 'µþÅÔÉÜ',
    '27' => 'ÂçºåÉÜ',
    '28' => 'Ê¼¸Ë¸©',
    '29' => 'ÆàÎÉ¸©',
    '30' => 'ÏÂ²Î»³¸©',
    '31' => 'Ä»¼è¸©',
    '32' => 'Åçº¬¸©',
    '33' => '²¬»³¸©',
    '34' => '¹­Åç¸©',
    '35' => '»³¸ý¸©',
    '36' => 'ÆÁÅç¸©',
    '37' => '¹áÀî¸©',
    '38' => '°¦É²¸©',
    '39' => '¹âÃÎ¸©',
    '40' => 'Ê¡²¬¸©',
    '41' => 'º´²ì¸©',
    '42' => 'Ä¹ºê¸©',
    '43' => '·§ËÜ¸©',
    '44' => 'ÂçÊ¬¸©',
    '45' => 'µÜºê¸©',
    '46' => '¼¯»ùÅç¸©',
    '47' => '²­Æì¸©' );
  //
  return $area_val[$i];
}

/**
 * 62¿Ê¿ôÊÑ´¹
 *
 * @access public
 * @param int $dec ÊÑ´¹Á°¤Î¿ôÃÍ:10¿Ê¿ôÁ°Äó
 * @return string ¿ôÃÍ¤ò62¿Ê¿ô¤ËÊÑ´¹
 */
static public function to62($dec)
{
  //
  $ar = array("0","1","2","3","4","5","6","7","8","9",
              "a", "b","c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
              "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
              "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
              "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
            );

  //
  $ret = "";

  do {
    $bottom = $dec % 62;
    $ret = $ar[$bottom] . $ret;
    $dec = (int)($dec/62);
  } while($dec);

  return $ret;
}

/**
 * ¶â³ÛÍÑ¥Õ¥©¡¼¥Þ¥Ã¥È
 *
 * £³·å¤´¤È¤Ë¶â³Û¤Ë¡¤(Àµ³Î¤Ë¤Ïdelimiter¤ÎÃÍ)¤ò¤Ö¤Á¹þ¤à
 * XXX Éé¤ÎÃÍ¤È¤«¤Þ¤À¥Æ¥¹¥È¤·¤Æ¤Ê¤¤¡Á
 *
 * @access public
 * @param int $i ¶â³Û
 * @param string $delimiter ¥Ç¥ê¥ß¥¿
 * @return string ¥Ç¥ê¥ß¥¿¤Ç¶èÀÚ¤é¤ì¤¿Ê¸»úÎó
 */
static public function money_format($i, $delimiter = ',')
{
  $awk = array();
  while(0 !== $i) {
    array_unshift($awk,  sprintf("%03d", $i % 1000));
    $i = (int)floor($i / 1000);
  }

  // XXX ÀèÆ¬Í×ÁÇ¤À¤±£°padding¤ò¼è¤ê½ü¤¯
  $awk[0] = (string)$awk[0] + 0;

  if (false === empty($awk)) {
    $ret = implode($delimiter, $awk);
  } else {
    $ret = '0';
  }

  //
  return $ret;
}

//private:


} // end of class

