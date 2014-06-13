<?php
/***************************************************
 *
 * Class Name : rss_item
 * Abstract   : RSS�θ�������
 *            : 
 * Author     : nakazawa
 * Date       : 2006/09/25
 *
 ***************************************************/

// class of rss_item start !!
class rss_item {

//  �ѿ������
private $title_;			//���ܸ�
private $link_;				//URL
private $pubDate_;			//����
private $guid_;				//URL��
private $description_;		//����ɡ���
private $enclosure_url_;
private $enclosure_length_;
private $enclosure_type_;
// XXX ���Ѥ������äƤϺٿ������դ�!!
private $contents_;

	//�������
	public function rss_item(){
		$this->init();
	}

	public function init(){
		$this->title_ = "";
		$this->link_ = "";
		$this->pubDate_ = "";
		$this->guid_ = "";
		$this->description_ = "";
		$this->enclosure_url_ = "";
		$this->enclosure_length_ = "";
		$this->enclosure_type_ = "";
		$this->contents_ = "";
	}

	//  �������å���
	public function setTitle($s){ $this->title_ = $s; }
	public function getTitle(){ return $this->title_; }
	public function setLink($s){ $this->link_ = $s; }
	public function getLink(){ return $this->link_; }
	public function setPubDate($s){ $this->pubDate_ = $s; }
	public function getPubDate(){ return $this->pubDate_; }
	public function setGuid($s){ $this->guid_ = $s; }
	public function getGuid(){ return $this->guid_; }
	public function setDescription($s){ $this->description_ = $s; }
	public function getDescription(){ return $this->description_; }

	public function setEnclosureUrl($s) { $this->enclosure_url_ = $s; }
	public function getEnclosureUrl() { return $this->enclosure_url_; }
	public function setEnclosureLength($s) { $this->enclosure_length_ = $s; }
	public function getEnclosureLength() { return $this->enclosure_length_; }
	public function setEnclosureType($s) { $this->enclosure_type_ = $s; }
	public function getEnclosureType() { return $this->enclosure_type_; }

	public function setContents($s) { $this->contents_ = $s; }
	public function getContents() { return $this->contents_; }

	//  ���������������ʤ���͡�

}	// end of class !!