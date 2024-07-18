#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

class ImageManager {		//ͼ�������
public:

	~ImageManager()
	{
		m_images.clear();
	}
	inline bool ExistImage(const string& name) const
	{
		return m_images.find(name) != m_images.end();
	}
	PIMAGE GetImage(const string& name)
	{
		if (!ExistImage(name))
		{
			ErrorLogTip("��������Ϊ\"" + name + "\"��ͼƬ��", "ImageManager::GetImage");
			return nullptr;
		}
		return m_images[name];
	}
	static string GetImageFullPath(const string& filename)
	{
		string path;
		if (ExistFile(path = ASSETS_DIR + filename))
			return path;
		if (ExistFile(path = COMMON_DIR + filename))
			return path;
		if (ExistFile(filename))
			return filename;
		ErrorLogTip("�޷���ȡͼ��ȫ·��, �ļ���Ϊ \"" + filename + "\"", "ImageManager::GetImageFullPath");
		return "";
	}
	void AddImage(const string& path, const string& name)
	{
		PIMAGE pimg = newimage();
		getimage(pimg, path.c_str());
		m_images.insert(make_pair(name, pimg));
	}
	void AddImage(const string& name)
	{
		string path{ GetImageFullPath(name) };
		if (path.empty())
			return;
		AddImage(path, name);
	}
	inline void AddImages(vector<string>&& names)
	{
		for (const auto& name : names)
			AddImage(name);
	}
	inline void AddImages(const vector<string>& names)
	{
		for (const auto& name : names)
			AddImage(name);
	}
	inline void AddImages(initializer_list<string>&& names)
	{
		for (const auto& name : names)
			AddImage(name);
	}
	inline void ClearImages()
	{
		m_images.clear();
	}
private:
	map<string, PIMAGE> m_images;

}imgMgr;