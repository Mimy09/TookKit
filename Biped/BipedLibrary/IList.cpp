#include "Biped\bpd\IList.h"

BPD_BEGIN
BPD_TEMPLATE_CLASS constexpr BPD_TEMPLATE_TYPE IList<BPD_TEMPLATE_TYPE>::operator[](size_type n)
	const { return n < size ? p[n] : BPD_EXCEPTION("Out Of Range");
};
BPD_TEMPLATE_CLASS constexpr const BPD_TEMPLATE_TYPE* IList<BPD_TEMPLATE_TYPE>::begin()
	const BPD_NOEXCEPT { return (&p[0]);
};
BPD_TEMPLATE_CLASS constexpr const BPD_TEMPLATE_TYPE* IList<BPD_TEMPLATE_TYPE>::end()
	const BPD_NOEXCEPT { return (&p[size]);
};
BPD_TEMPLATE_CLASS constexpr size_type IList<BPD_TEMPLATE_TYPE>::length()
	const BPD_NOEXCEPT { return (size);
};
BPD_TEMPLATE_CLASS constexpr const BPD_TEMPLATE_TYPE* IList<BPD_TEMPLATE_TYPE>::data()
	const BPD_NOEXCEPT { return (p);
};
BPD_TEMPLATE_CLASS void IList<BPD_TEMPLATE_TYPE>::editable(value_type * a)
	BPD_NOEXCEPT {
	BPD_SAFE_DELETE(a);
	a = new value_type[size];
	for(u_int i = 0; i < size; i++) a[i] = p[i];
};
BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE* IList<BPD_TEMPLATE_TYPE>::editable()
	BPD_NOEXCEPT {
	value_type * temp = new value_type[size];
	for(u_int i = 0; i < size; i++) temp[i] = p[i];
	return temp;
};
BPD_TEMPLATE_DEFAULT(IList)
BPD_END