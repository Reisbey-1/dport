// dllmain.h : Declaration of module class.

class CDPortModule : public CAtlDllModuleT< CDPortModule >
{
public :
	DECLARE_LIBID(LIBID_DPortLib)
//	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DPORT, "{0ADC9463-8592-45B6-846C-6162DD95CF3A}")
};

extern class CDPortModule _AtlModule;
