<?php
/**
 * RSS �ǡ������饹
 *
 * RSS��ɽ����
 * RSS�����ͥ�ȸ������Ǥǹ��������
 *
 * @package magicweapon
 * @access  public
 * @author  nakazawa
 * @create  2006/09/25
 * @version $Id$
 **/

// class of rss_data start !!
class rss_data {
  
  //�������
  public function rss_data(){
    $this->init();
  }

  public function init(){
    $this->channleObj_ = "";
    $this->itemObjAry_ = array();    // �ɤ��ʤ�����͡����ν�����ϡ�
    $this->cursor_ = -1;
  }

  //  �������å���
  public function setChannelObj($o){ $this->channelObj_ = $o; }
  public function getChannelObj(){ return $this->channelObj_; }

  public function putItem($o){ array_push( $this->itemObjAry_,$o ); }
  public function getAllItems(){ return $this->itemObjAry_; }
  // ��setter�Ϥ���ʤ���͡���

  //  �̤�Τ������졣����
  public function getItemObj(){ return $this->itemObjAry_[$this->getPos()]; }
  public function cntItems(){ return count($this->itemObjAry_); }

  public function clrPos(){ $this->cursor_ = -1; }
  public function incPos(){ $this->cursor_ += 1 ; }
  public function getPos(){ return $this->cursor_; }

  //  ����

  //  �ݥ��󥿤򥤥󥯥���Ȥ��Ƽ����������Ǥ򼨤���
  public function fetchItems(){
    //���Ȥꤢ�������󥯥���Ȥ��ơ�����
    $this->incPos();

    if($this->getPos() >= $this->cntItems()){
      //  ����������������ϰϤ�Ķ������ä��衪
      $this->clrPos();
      return false;
    }
    return true;
  }

  //  ������ʤ�������ե��å��ϤΥ��˥���饤����
  //  �äƤ��Ȥϥݥ��󥿡��Υ��ꥢ�Ǥ����Τ��ʡ�
  public function fetchItemsInit(){
    $this->clrPos();
  }

  //  �ѿ������
  private $channelObj_;    //�����ͥ�Obj
  private $itemObjAry_;    //itemObj����Ǽ���������
  private $cursor_;      //�ݥ��󥿡�����

}  // end of class !!