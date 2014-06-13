<?php

/**
 * �ȡ����ʥ�����
 *
 * ��ˡ����ʥȡ��������������
 * XXX �ޤ�����ξ����ǥ�ˡ����ˤʤ�Ȼפ��ޤ�
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 */
require_once('code_util.inc');

class tokenizer 
{

/**
 * _get
 * �ᥤ������å�
 *
 */
static public function _get($delimiter, $flg_ran, $flg_pid, $flg_ip)
{
$tokens = array();
  // �á��ޥ������ä����
  // XXX �Ĵؿ��������ͤ�����ǥ�ߥ�������������
  list($usec, $sec) = explode(" ", microtime());
  
  // �����ϥǥե����
  // ���ݥå��á��ޤ������Ϥ����ΤǤ���äȾ������
  $tokens[] = $sec - 1079340000;
  // �ޥ�������
  $tokens[] = (int)($usec * 1000 * 1000);

  // ���
  if ($flg_ran) {
    $tokens[] = mt_rand();
  }

  // �ץ�����ID
  if ($flg_pid) {
    $tokens[] = getmypid();
  }

  // XXX thread ID ��PHP���ȼ��ʤ� ����

  // IP���ɥ쥹
  if ($flg_ip) {
    $tokens[] = str_replace(".", "", $_SERVER['REMOTE_ADDR']);
  }

  // �ǡ�����
  $ret = array();
  foreach($tokens as $token) {
    $ret[] = code_util::to62($token);
  }
  return implode($delimiter, $ret);
}


/**
 * get
 * �Ȥꤢ�����ǥե���ȤäƤ��Ȥ�
 *
 */
static function get($delimiter = "-")
{
  // �Ȥꤢ��������ܥץ�����ID
  // XXX �ޡ�����ʤ�������
  return tokenizer::_get($delimiter, true, true, false);
}


} // end of class
