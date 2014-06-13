<?php

/**
 * view クラス 絵文字付き
 *
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('view_mobile.inc');
require_once('emoji_adapter_Text_Pictogram_Mobile.inc');

class view_adapter_Text_Pictogram_Mobile extends view_mobile {

public function output_extra($s) {
  //
  $s = parent::output_extra($s);

  // 絵文字変換
  $pobj = emoji_adapter_Text_Pictogram_Mobile::get_obj( $this->get_model_obj()->get_mobile());

  //
  $s = $pobj->restore($s);

  //
  return $s;
}

//private:


} // end of class

