<?php

/**
 * IS���饹
 *
 * �͡���ʸ����Ƚ���ѥ��饹
 * ����Ū�� is::�᥽�å�̾ �ǻȤ�����
 * XXX �Ȥꤢ��������ɽ�����Ť����餽�Τ��������������ʤ�
 * XXX ����ɽ�����Τ⡢POSIX Regex �� Perl Regex �Ⱥ����äƤ뤷��
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

// is_date��
require_once('calendar.inc');

class is
{


/**
 * is_alphanum
 *
 */
static public function is_alphanum($s){
/*
  if (ereg ("[^0-9a-zA-Z]", $s)) {
    return false;
  }
  return true;
*/
  return ctype_alnum($s);
}


/**
 * is_digit
 *
 */
static public function is_digit($num){
/*
  if (ereg ("[^0-9]", $num)) {
    return false;
  }
  return true;
*/
  return ctype_digit($num);
}

  /**
   * is_kana
   *
   */
  static public function is_kana($str){
    if(!ereg( "^(\xA5[\xA1-\xF6]|\xA1\xBC|\xA1\xA6|\xA1\xA1|\x20)+$", $str)){
      return false;
    }
    return true;
  }

  /**
   * is_email 
   *
   *
   */
  static public function is_email ($mail) {
    if (!ereg ("[0-9a-zA-Z\.\-]@[0-9a-zA-Z\.\-]", $mail)) {
      return false;
    } else {
      // �ɥᥤ����ʬ�Υ����å�
      $domain = ereg_replace ("[^@]*@", "", $mail);
      if (ereg ("[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}", $domain)) {
        // �ɥᥤ����ʬ��IP���ɥ쥹���ä����ν���
        $ip = explode (".", $domain);
        for ($i = 0; $i < 4; $i++) {
          if (strlen($ip[$i]) == 0 || $ip[$i] > 255) {
            $x = "error";
            break;
          }
        }
        if ($x) {
          return false;
        }
      // IP�Ǥʤ����Υɥᥤ������å�
      }else if(is::is_domain($domain)){
        // �ɥᥤ������ʸ���������å�
        if(255 < strlen($domain)){
          return false;
        }
      }else{
        return false;
      }
      // ����������ʬ�Υ����å�
      $local = substr($mail,0,strrpos($mail,"@".$domain));
      // ������������ʸ���������å�
      if(64 < strlen($local)){
        return false;
      }
      // ������ץ�����ػߤ��뤿��ˡ��϶ػߡ����롪��
      if(ereg("<|>",$local)){
        return false;
      }
    }
    return true;
  }

  /**
   * is_domain
   *
   *
   */
  static public function is_domain($domain){
    //$chars = "((([a-zA-Z0-9])|([a-zA-Z0-9])(([a-zA-Z0-9])|-)*([a-zA-Z0-9])))*(([a-zA-Z])|([a-zA-Z])(([a-zA-Z0-9])|-)*([a-zA-Z0-9]))+\.?";
    $chars = "(^[0-9a-zA-Z]+[0-9a-zA-Z\-]*[0-9a-zA-Z]{1}\.{0,1})*[0-9a-zA-Z]{1}$";
    if(!ereg($chars, $domain)){
      return false;
    }
    return true;
  }

  //
  static public function is_url($url){
    if (preg_match('/^(https?|ftp)(:\/\/[-_.!~*\'()a-zA-Z0-9;\/?:\@&=+\$,%#]+)$/
', $url)) {
      return true;
    }
    // else 
    return false;
  }

/**
 * is_dir
 * �ǥ��쥯�ȥ�̾
 * XXX ���̡��ѿ�����_-��ͭ���Ȥ���
 *
 */
static function is_dir($s) {
  if (preg_match("/[^0-9a-zA-Z\-_]+/", $s)) {
    return false;
  }
  return true;
}

/**
 * ����
 *
 */
static function is_date($s) {
  $cal = new calendar;
  $cal->set_string($s);

  //
  return $cal->is();
}

// XXX
// ���������ѥ������ʤΤߤǹ�������Ƥ���п�
// ��������ʸ�������ɤ����꤬����Ƥ���ɬ�פ�����ޤ���
// ����
// mb_regex_encoding('euc-jp');
public static function is_katakana($s) {
mb_regex_encoding('euc-jp');
  $ret = mb_ereg("^[�����������������������������������ĥƥȥʥ˥̥ͥΥϥҥեإۥޥߥ��������������󥬥��������������������¥ťǥɥХӥ֥٥ܥѥݥԥץڥݥ����������å��硼]*$", $s);
  // XXX ����ʤΤǤȤꤢ�������ä���
  if (false === $ret) {
    return false;
  }
  // else
  return true;
}

// is_zip
public function is_zip($s)
{
  if (preg_match("/^[0-9][0-9][0-9][\- ]?[0-9][0-9][0-9][0-9]$/", $s)) {
    return true;
  }
  // else
  return false;
}

// is_zip2
public function is_zip2($s1, $s2)
{
  if (3 !== strlen($s1)) {
    return false;
  }
  if (4 !== strlen($s2)) {
    return false;
  }
  // XXX �ޤȤ��
  return is::is_digit($s1)&&is::is_digit($s2);
}


// is_tel
public function is_tel($s)
{
  if (preg_match("/^0[0-9]{1,4}[\- ]?[0-9]{1,4}[\- ]?[0-9]{4}$/", $s)) {
    return true;
  }
  // else
  return false;
}

// is_tel3



} // end of class