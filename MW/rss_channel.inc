<?php
/**
 * RSS �����ͥ륯�饹
 *
 * RSS�Υإå���ʬ�δ���
 *
 * @package magicweapon
 * @access  public
 * @author  nakazawa
 * @create  2006/09/25
 * @version $Id$
 **/


// class of rss_channel start !!
class rss_channel {
  //�������
  public function rss_channel(){
    $this->init();
  }

  public function init(){
    $this->title_ = "";
    $this->linkTop_ = "";
    $this->description_ = "";
    $this->language_ = "";
    $this->copyright_ = "";
    $this->image_url_ = "";
    $this->image_link_ = "";
    $this->image_title_ = "";
  }

  //  �������å���
  public function setTitle($s){ $this->title_ = $s; }
  public function getTitle(){ return $this->title_; }
  public function setLinkTop($s){ $this->linkTop_ = $s; }
  public function getLinkTop(){ return $this->linkTop_; }
  public function setDescription($s){ $this->description_ = $s; }
  public function getDescription(){ return $this->description_; }
  public function setLanguage($s){ $this->language_ = $s; }
  public function getLanguage(){ return $this->language_; }
  public function setCopyright($s){ $this->copyright_ = $s; } 
  public function getCopyright(){ return $this->copyright_; }
  public function setImageLink($s){ $this->image_link_ = $s; }
  public function getImageLink(){ return $this->image_link_; }
  public function setImageUrl($s){ $this->image_url_ = $s; }
  public function getImageUrl(){ return $this->image_url_; }
  public function setImageTitle($s){ $this->image_title_ = $s; }
  public function getImageTitle(){ return $this->image_title_; }

  public function setCss($s){ $this->css_ = $s; }
  public function getCss(){ return $this->css_; }

  //  ����  ����������Τ���


  //���ѿ������
  private $title_;    //���Υ����ȥ�
  private $linkTop_;    //Page URL
  private $description_;  //����ɡ���
  private $language_;    //���졣ja�����ä�
  private $copyright_;  //���Ԥ��餤��
  private $image_url_;  //�����ͥ�Υ���ͥ��륤�᡼��URL
  private $image_link_;  //�����ͥ�Υ���ͥ��륤�᡼�������
  private $image_title_;  //�����ͥ�Υ���ͥ��륤�᡼�������ȥ�

  //
  private $css_;	// CSS

}  // end of class!!