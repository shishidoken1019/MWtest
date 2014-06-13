<?php

//
// RSS�����ȥץåȤδ��쥯�饹
//

require_once("conv.inc");
require_once("conv_util.inc");

abstract class rss_output_base
{
// public 

public function __construct() { $this->init(); }
public function init() {
  $this->rss_obj_  = null;
}

public function set_data(rss_data $obj) { $this->rss_obj_ = $obj; }

/**
 * get_string
 * rss_data���֥������Ȥξ��󤫤�RSS�������ȥ�󥰤Ȥ����֤���
 * ���ܤϡ�ʢ�ˤ��������ƥ�ץ졼�Ȥ��ִ����Ƥ�����
 */
public function get_string() {

  //////
  // rss_data�����뤫�����å�

  if(null == $this->_rss_obj()){  // rss_data��null�ʤ齪λ��
//print "rss_obj is null!\n";
    return "";                    // ����ͤϥ��ȥ�󥰤ʤΤǶ�ʸ����
  }

  //
  $rssdata = $this->_rss_obj();   // RSS�Υǡ�������Ǽ���줿���֥�������
  $conv    = new f_conv();        // �ƥ�ץ졼���ִ����Ƥ����

  //////
  // channel��ʬ��ñ�ִ�

  $channel = $rssdata->getChannelObj();

  $conv->monoDic("channel_language", $channel->getLanguage());
  //$conv->monoDic("channel_about", "����Υե�����̾");
  $conv->monoDic("channel_title", $channel->getTitle());
  $conv->monoDic("channel_link", $channel->getLinkTop());
  $conv->monoDic("channel_description", $channel->getDescription());
  $conv->monoDic("channel_copyright", $channel->getCopyright());

  // CSS
  // XXX ���礤�Ȥ��뤤�����
//print_r($channel);
  if ("" != $channel->getCss()) {
    $css_obj = new simple_put();
    $conv->multiDic("channel_css_put", $css_obj);
    $conv->monoDic("channel_css_url", $channel->getCss());
  }


  //////
  // image��ʬ��ñ�ִ�

  $conv->monoDic("image_resource", $channel->getImageUrl());
  $conv->monoDic("image_about", $channel->getImageUrl());
  $conv->monoDic("image_url", $channel->getImageUrl());
  $conv->monoDic("image_title", $channel->getImageTitle());
  $conv->monoDic("image_link", $channel->getImageLink());

  //////
  // textinput��ʬ��ñ�ִ�
/*
  // rss_data���֥������Ȥ�����̤������

  $conv->monoDic("textinput_resource", $channel->get());
  $conv->monoDic("textinput_about", $channel->get());
  $conv->monoDic("textinput_title", $channel->get());
  $conv->monoDic("textinput_description", $channel->get());
  $conv->monoDic("textinput_name", $channel->get());
  $conv->monoDic("textinput_link", $channel->get());
*/

  //////
  // fetch���ʤ���multiDic���Ϥ����֥������Ȥ����
  // "rdf:li"��ʬ��<item>��ʬ��Ʊ���ˡ�

  $liloop   = new li_loop();    // m_conv������obj(rdf:li��ʬ)
  $itemloop = new item_loop();  // m_conv������obj(<item>��ʬ)
  while($rssdata->fetchItems()) {
    $liloop->add_data($rssdata->getItemObj());
    $itemloop->add_data($rssdata->getItemObj());
  }
  $conv->multiDic("li_loop", $liloop);
  $conv->multiDic("item_loop", $itemloop);

  $ret = $conv->conv($this->rss_template());
  return $ret;
}

// protected
protected function _rss_obj() { return $this->rss_obj_; }

/**
 * RSS�Υƥ�ץ졼�ȣ��ܤ�ʸ������֤���
 * �С�����󤴤ȡ����뤤�Ϥ��λ����Ѥ������Ǥʤɤ˱�����
 * Ŭ���ѹ����Ʋ�������
 *
 * ����� : string
 * ���� : ̵��
 */
abstract protected function rss_template();

//private
private $rss_obj_;   // RSS�Υǡ������ݻ����Ƥ��륪�֥�������
                                   
};  // end of class

////////////////////////////////////////////////////////////////
// XXX multiDic���Ϥ���(m_conv()����äƤ�)���饹
// �Ȥꤢ���������˽񤯡�����ǹԤ��ȷ�ޤä���
// �̥ե�����ˤ��뤫�⡩(�⤷����simple_loop���ѤȤ�)

class li_loop
{
// public 
  public function __construct() { $this->init(); }
  public function init() { $this->data_ = array(); }

  public function add_data(rss_item $obj) { $this->data_[] = $obj; }
  public function set_data(array $ary) {
    foreach($ary as $a) { $this->add_data($a); }
  }

  public function m_conv($body, $param) {

    //////
    // �ǡ�����������ʤ齪λ
    if (0 == count($this->data_)) { 
//print "li_loop: data is empty!\n";
      return "";
    } 
    
    //////
    // �ִ����ʤ���롼��
    $ret = "";  // ��̳�Ǽ��
    $c   = new f_conv();
    foreach ($this->data_ as $d) {  // $d��rss_item���֥�������
      $c->monoDic("li_resource", $d->getLink());
      $ret .= $c->conv($body);
    }

    //////
    // ����
    return $ret;
  }

// private
  private $data_ = array();  // rss_item������
                             // XXX ���ξ��̵�̤ʥǡ�����¿�����ɡ�
};

//
// ��Υ��饹�Ȥ��֤�ޤ�������ɡ�
// ���̲������Ϥ���ǹԤ��ȳ��ꤷ�Ƥ��顣
//
class item_loop
{
// public 
  public function __construct() { $this->init(); }
  public function init() { $this->data_ = array(); }

  public function add_data(rss_item $obj) { $this->data_[] = $obj; }
  public function set_data(array $ary) {
    foreach($ary as $a) { $this->add_data($a); }
  }

  public function m_conv($body, $param) {

    //////
    // �ǡ�����������ʤ齪λ
    if (0 == count($this->data_)) {
//print "item_loop: data is empty!\n";
      return "";
    } 
    
    //////
    // �ִ����ʤ���롼��
    $ret = "";  // ��̳�Ǽ��
    $c   = new f_conv();
    foreach ($this->data_ as $d) {  // $d��rss_item���֥�������
      $c->monoDic("item_about", $d->getLink());
      $c->monoDic("item_title", $d->getTitle());
      $c->monoDic("item_link", $d->getLink());
      $c->monoDic("item_description", $d->getDescription());
      $c->monoDic("item_contents", $d->getContents());
      $c->monoDic("item_pubDate", $d->getPubDate());
      $c->monoDic("item_guid", $d->getGuid());
      $c->monoDic("enclosure_url", $d->getEnclosureUrl());
      $c->monoDic("enclosure_length", $d->getEnclosureLength());
      $c->monoDic("enclosure_type", $d->getEnclosureType());
      $ret .= $c->conv($body);
    }

    //////
    // ����
    return $ret;
  }

// private
  private $data_ = array();  // rss_item������

};
