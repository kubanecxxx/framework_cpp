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

template<class T> class guiDoubleLinkedListClasstemp: public gui_New
{
public:
	guiDoubleLinkedListClasstemp()
	{
		p_next = 0;
		p_prev = 0;
	}

	T * p_next;
	T * p_prev;
};

template<class T> class guiDoubleLinkedListClass
{
public:
	guiDoubleLinkedListClass()
	{
		list = new guiDoubleLinkedListClasstemp<T>;
	}
	inline T * GetNext()
	{
		return list->p_next;
	}
	inline T * GetPrev()
	{
		return list->p_prev;
	}
	inline void SetNext(T * next)
	{
		list->p_next = next;
	}
	inline void SetPrev(T * prev)
	{
		list->p_prev = prev;
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

			do
			{
				temp = temp->GetNext();
			} while (temp->GetNext() != 0);

			temp->SetNext(item);
			item->SetPrev(temp);
		}

		Count++;

		return item;
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

	T * WriteToFlash(void);

private:
	guiDoubleLinkedListClasstemp<T> * list;
};


template <class T>
T * guiDoubleLinkedListClass<T>::WriteToFlash(void)
{
	return (T *)gui_FlashWrite::Write(this, sizeof(T));
}

} /* namespace GuiFramework */

#endif /* GUIDOUBLELINKEDLISTCLASS_H_ */
