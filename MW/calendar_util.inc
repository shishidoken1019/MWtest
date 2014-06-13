<?php

/**
 * calenderのutil
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('calendar.inc');

class calendar_util {

/**
 * 「今この瞬間の日付をstringで」をげと
 *
 * @access public
 * @return string 日付のstring yyyy-mm-dd hh:mm:ss の書式
 */
static public function get_now_string()
{
  $obj = new calendar;
  $obj->set_now_date();
  return $obj->get_string('-');
}

/**
 * convにデータを設定：年月日別々に
 *
 * @access public
 * @return string 日付のstring yyyy-mm-dd hh:mm:ss の書式
 */
static public function set_to_conv(f_conv $conv, calendar $cal, $prefix = "")
{
  $conv->monoDic($prefix . 'yy', $cal->get_year());
  $conv->monoDic($prefix . 'mm', $cal->get_month());
  $conv->monoDic($prefix . 'dd', $cal->get_day());
  $conv->monoDic($prefix . 'h', $cal->get_hour());
  $conv->monoDic($prefix . 'm', $cal->get_minute());
  $conv->monoDic($prefix . 's', $cal->get_second());
}



//private:


} // end of class

