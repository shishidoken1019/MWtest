<?php

/**
 * CGI �ꥯ�����ȥ��饹 ��ʸ����åѡ�
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('cgi_request.inc');
require_once('emoji_adapter_Text_Pictogram_Mobile.inc');

//
class cgi_request_adapter_Text_Pictogram_Mobile extends cgi_request {

/**
 * Text_Pictogram_Mobile ����
 *
 * @access public
 * @param string $s �ǡ���
 * @return string ����
 */
public function interruption_emoji($s)
{
  // ��ʸ���Ѵ�
  $pobj = emoji_adapter_Text_Pictogram_Mobile::get_obj( new mobile_info );

  //
  $s = $pobj->convert($s);

  //
  return $s;
}

//private:

} // end of class
