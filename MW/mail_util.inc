<?php

/**
 * mail�ѥ桼�ƥ���ƥ����饹
 *
 * mail�ѤΥ桼�ƥ���ƥ����饹
 * �桼�ƥ���ƥ��ϥ��饹�ʤΤǡ�����
 * mail_util::�᥽�å�
 * �η����Ǥ�call�����ꤷ�Ƥ���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class mail_util {


/**
 * �᡼�륢�ɥ쥹��ȴ���Ф�
 *
 * ̾�� <�᡼�륢�ɥ쥹> �η������顢�᡼�륢�ɥ쥹������ȴ���Ф�
 *
 * @access public
 * @param string $s �᡼�륢�ɥ쥹
 * @return string ȴ���Ф������ɥ쥹��ʬ�����顼�϶�ʸ������
 */
static public function carve_address($s)
{
  if (1 === preg_match('/[<](.*?)[>]/', $s, $mt)) {
    return $mt[1];
  }
  // else
  return trim($s);
}

/**
 * ���ѥ���٥����ץ꥿����ѥ� (VERP : variable envelope return path) ����
 *
 * ���顼�᡼�����������ѤΤ��ˤ��
 * ��)
 * mail_util::make_verp('error@test.com', 'm.furusho@gmail.com');
 * ��
 * error+m.furusho=gmail.com@test.com
 * �ˤ��롣
 *
 * @access public
 * @param string $e ���顼��ã�ѥ᡼�륢�ɥ쥹
 * @param string $t to�᡼�륢�ɥ쥹(���������
 * @param string $d �᡼�륢�ɥ쥹�Υǥ�ߥ� : �Ȥꤢ����Postfix�Υǥե��ܤ�
 * @return string return-path�����ꤹ�٤��᡼�륢�ɥ쥹
 */
static public function make_verp($e, $t, $d = '+')
{
  // �ޤ�ʬ��
  $wk = explode('@', $e);

  // to���ɥ쥹�Ρ����ִ�
  $t = strtr($t, '@', '=');

  // ­�����������
  $s = $wk[0] . $d . $t . '@' . $wk[1];
  return $s;
}

} // end of class
