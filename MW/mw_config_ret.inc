<?php

/**
 * "mw_config���饹���������ѥ��饹
 *
 * mw_config���饹�Ȱ��˽񤤤Ƥ�褫�ä�������ɤͤ���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class mw_config_ret {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
  $this->set_include_filename('');
  $this->set_classname('');
  $this->set_template_filename('');
  $this->set_error_template_filename('');
  $this->set_ssl_type('');
}

/**
 * include���٤��ե�����̾�μ���
 *
 * @access public
 * @return string include���٤��ե�����̾
 */
public function get_include_filename() { return $this->include_filename_; }
public function set_include_filename($s) { $this->include_filename_ = $s; }

/**
 * new���٤�class̾�μ���
 *
 * @access public
 * @return string new���٤�class̾
 */
public function get_classname() { return $this->classname_; }
public function set_classname($s) { $this->classname_ = $s; }

/**
 * �̾��ѥƥ�ץ졼�ȥե�����̾�μ���
 *
 * @access public
 * @return string �̾��ѥƥ�ץ졼�ȥե�����̾
 */
public function get_template_filename() { return $this->template_filename_; }
public function set_template_filename($s) { $this->template_filename_ = $s; }

/**
 * error�ѥƥ�ץ졼�ȥե�����̾�μ���
 *
 * @access public
 * @return string error�ѥƥ�ץ졼�ȥե�����̾
 */
public function get_error_template_filename()
  { return $this->error_template_filename_; }
public function set_error_template_filename($s)
  { $this->error_template_filename_ = $s; }

/**
 * ssl�����פμ���
 *
 * �����ssl��nossl��not_care��3type�����ꤷ�Ƥ뤱��
 * �ºݤˤϤ����ϡֳ�ĥ�ΰ�װ����ˤʤ�Ȼפ�
 *
 * @access public
 * @return string ssl������
 */
public function set_ssl_type($s) { $this->ssl_type_ = $s; }
public function get_ssl_type() { return $this->ssl_type_; }


//private:
private $include_filename_;
private $classname_;
private $template_filename_;
private $error_template_filename_;
private $ssl_type_;

} // end of class
