<?php

/**
 * security���饹
 *
 * ���ܤϥ��˥������������å�
 *
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

class security
{

// HTML��(XSS�й�)���˥�����
static public function sanitize_html($base_string)
{
  // XXX �Ȥꤢ����htmlsppuecialchars �Ȥ��������ꤢ�ä���®������!!
  // XXX htmlentities��Ŭ���ϰϤ��⤦��������ʤΤ��ݤ�����Ȥ��
  // XXX ���󥰥륯�����Ȥ⥨�������פ��Ƥ��������Τ� ENT_QUOTES �� add
  return htmlspecialchars($base_string, ENT_QUOTES);
}


//����ɽ���ѤΥ��˥�����
static public function sanitize_regex($base_string)
{
  $ret = "";
  // XXX �����Τߤλ���int��������ʤ��褦�ˡ��ĥ���٥󤷤Ƥ��졨��
  $base_string = $base_string . "";

  $length = strlen($base_string);
  for($i = 0; $i < $length; $i ++) {
    $itr = $base_string[$i];
    switch($itr) {
      // �ʲ���ʸ���� '\'�ǥ��������פ��Ƥ���
      case '#':
      case '/':
      case '?':
      case '*':
      case '+':
      case '^':
      case '$':
      case '.':
      case '[':
      case ']':
      case '|':
      case '(':
      case ')':
      case '{':
      case '}':
      case '-':
      case '\\':
        $ret .= '\\';
        break;

      default:
        break;
    }
    $ret .= $itr;
  }
  //
  return $ret;
}

// DB�ѤΥ��˥�����
static public function sanitize_db($base_string)
{
  // XXX addslashes �ϥХ��äƤ�ΤǻȤ�ʤ�!!
  // return addslashes($base_string);

  // ����
$ret = "";
  // XXX �����Τߤλ���int��������ʤ��褦�ˡ��ĥ���٥󤷤Ƥ��졨��
  $base_string = $base_string . "";
  $length = strlen($base_string);
  for($i = 0; $i < $length; $i ++) {
    $itr = $base_string[$i];
    switch($itr) {
      // �ʲ���ʸ���� '\'�ǥ��������פ��Ƥ���
      case '\'':
      case ';':
      case '"':
      case '\\':
        $ret .= '\\';
        break;


      default:
        break;
    }
    $ret .= $itr;
  }

  //
  return $ret;
}

// ��������
static public function sanitize_db_add_quote($base_string, $quote_string = "'")
{
  // �ޤ����˥�����
  $ret = security::sanitize_db($base_string);

  // �������Ȥ�Ĥ���
  if($ret === '')
	  return "null";
  else
	  return $quote_string . $ret . $quote_string;
  
}

// header Injection��
// XXX �Ȥꤢ����ñ���CRLF����
static public function sanitize_header_fields_data($base_string)
{
  $ret = preg_replace('/[\r\n]/', '', $base_string);
  return $ret;
}

} // end of class
