/**
 * @file guiDoubleLinkedListClass.h
 * @author kubanec
 * @date 2.9.2012
 *
 */

#ifndef GUIDOUBLELINKEDLISTCLASS_H_
#define GUIDOUBLELINKEDLISTCLASS_H_

namespace GuiFramework
{

template<class T> class guiDoubleLinkedListClasstemp
{
public:
	guiDoubleLinkedListClasstemp()
	{
		p_next = 0;
		p_prev = 0;
	}
public:
	T * p_next;
	T * p_prev;
};

/**
 * @brief double linked list
 *
 * má všechno co je potřeba pro linkovanej seznam,
 * widgety si to můžou zdědit se svym templatem a můžou veselet přeskakovat jeden na druhyho
 * a registrovat se mezi sebou a tak
 */
template<class T> class guiDoubleLinkedListClass
{
public:
	guiDoubleLinkedListClass()
	{
		list = new guiDoubleLinkedListClasstemp<T>;
	}
	inline T * GetNext() const
	{
		return list->p_next;
	}
	inline T * GetPrev() const
	{
		return list->p_prev;
	}
	inline bool HasNext() const
	{
		return (list->p_prev != NULL);
	}

private:
	inline void SetNext(T * next)
	{
		list->p_next = next;
	}
	inline void SetPrev(T * prev)
	{
		list->p_prev = prev;
	}

	static T * GetFromIndex(T * first, uint8_t index, uint8_t Count)
	{
		T * temp = first;

		if (Count <= index)
			return 0;

		for (int i = 0; i < index; i++)
		{
			temp = temp->GetNext();
		}

		return temp;
	}

	static T * Register(T * item, uint8_t & Count, T * & FIRST)
	{
		T * temp;
		if (Count == 0)
		{
			item->SetPrev(0);
			item->SetNext(0);
			FIRST = item;
		}
		else
		{
			temp = FIRST;

			for (int i = 1; i < Count; i++)
			{
				temp = temp->GetNext();
			}

			temp->SetNext(item);
			item->SetPrev(temp);
		}

		Count++;

		return item;
	}

	virtual T * WriteToFlash(void);

private:
	guiDoubleLinkedListClasstemp<T> * list;
	friend class gui_Screen;
};

template<class T>
T * guiDoubleLinkedListClass<T>::WriteToFlash(void)
{
	return (T *) gui_FlashWrite::Write(this, sizeof(T));
}

} /* namespace GuiFramework */

#endif /* GUIDOUBLELINKEDLISTCLASS_H_ */
