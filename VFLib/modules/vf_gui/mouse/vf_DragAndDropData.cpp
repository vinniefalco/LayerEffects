/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

DragAndDropData::DragAndDropData ()
{
}

DragAndDropData::~DragAndDropData ()
{
  for (Items::iterator iter = m_items.begin (); iter != m_items.end ();)
  {
    Item* item = &(*iter++);
    delete item;
  }
}

/*============================================================================*/

bool DragAndDropData::Target::isInterestedInDragSource (const SourceDetails& dragSourceDetails)
{
  DragAndDropData* data = dragSourceDetails.description.isObject () ?
    dynamic_cast <DragAndDropData*> (dragSourceDetails.description.getObject ()) :
    0;
  if (data)
    return this->isInterestedInDragSource (*data, dragSourceDetails);
  else
    return false;
}

void DragAndDropData::Target::itemDragEnter (const SourceDetails& dragSourceDetails)
{
  DragAndDropData* data = dragSourceDetails.description.isObject () ?
    dynamic_cast <DragAndDropData*> (dragSourceDetails.description.getObject ()) :
    0;
  if (data)
    this->itemDragEnter (*data, dragSourceDetails);
}

void DragAndDropData::Target::itemDragMove (const SourceDetails& dragSourceDetails)
{
  DragAndDropData* data = dragSourceDetails.description.isObject () ?
    dynamic_cast <DragAndDropData*> (dragSourceDetails.description.getObject ()) :
    0;
  if (data)
    this->itemDragMove (*data, dragSourceDetails);
}

void DragAndDropData::Target::itemDragExit (const SourceDetails& dragSourceDetails)
{
  DragAndDropData* data = dragSourceDetails.description.isObject () ?
    dynamic_cast <DragAndDropData*> (dragSourceDetails.description.getObject ()) :
    0;
  if (data)
    this->itemDragExit (*data, dragSourceDetails);
}

void DragAndDropData::Target::itemDropped (const SourceDetails& dragSourceDetails)
{
  DragAndDropData* data = dragSourceDetails.description.isObject () ?
    dynamic_cast <DragAndDropData*> (dragSourceDetails.description.getObject ()) :
    0;
  if (data)
    this->itemDropped (*data, dragSourceDetails);
}
