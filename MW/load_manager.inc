<?php

/**
 * �����ɥޥ͡����㥯�饹
 *
 * �֥��顼�ȥ�åפΤǤ����require��¸����뤿��Υ��饹
 * XXX Perl���ȷ빽��̣�����뤫�¸��Ǥ��ʤ����饹�ˤʤꤽ��������
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/


class load_manager {
//public:

/**
 * static�˻Ȥ��뤳�Ȥ�����ˤ��Ƥ���
 * @access	public
 * @param	string	$filename	reuqire�������ե�����̾
 * @return	boolean	����������true�����Ԥ�����false
 */
static public function load_file($filename)
{
/*
  // �ե�����¸�ߥ����å�
  // �ե����뤬�ºߥե�����ǤϤʤ�
  if (!(is_file($filename))) {
    // ���ĥ�󥯥ե�����Ǥ�ʤ����
    if (!(is_link($filename))) {
      return false;
    }
  }
*/

  // XXX require���ȥ��顼��ª�Ǥ��ʤ��ΤǤ����Ƥ�include
//print "in to load_file $filename \n";
  $ret = @include_once($filename);
//print "ret is \n";
//var_dump($ret);
  if (false === $ret) {
    return false;
  }
  // else
  return true;
}

} // end of class