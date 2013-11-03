/*  XmlUtil.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "XmlUtil.h"

#include <QTextStream>
#include <iostream>


namespace libglabels
{

	Units *XmlUtil::mDefaultUnits;


	QString  XmlUtil::getAttr( const QDomElement &node, const QString &name, const char *default_value )
	{
		return node.attribute( name, QString(default_value) );
	}


	QString  XmlUtil::getAttr( const QDomElement &node, const QString &name, const QString &default_value )
	{
		return node.attribute( name, default_value );
	}


	double   XmlUtil::getAttr( const QDomElement &node, const QString &name, double default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			double value = valueString.toDouble( &ok );

			if ( !ok )
			{
				std::cerr << "Error: bad double value in attribute "
					  << qPrintable( node.tagName() ) << ":" << qPrintable( name )
					  << " : '" << qPrintable( valueString ) << "'"
					  << std:: endl;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	bool     XmlUtil::getAttr( const QDomElement &node, const QString &name, bool default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			int intValue = valueString.toInt();

			if ( (valueString == "True") ||
			     (valueString == "TRUE") ||
			     (valueString == "true") ||
			     (intValue == 1) )
			{
				return true;
			}

			if ( (valueString == "False") ||
			     (valueString == "FALSE") ||
			     (valueString == "false") ||
			     (intValue == 0) )
			{
				return false;
			}

			std::cerr << "Error: bad boolean value in attribute "
				  << qPrintable( node.tagName() ) << ":" << qPrintable( name )
				  << " : '" << qPrintable( valueString ) << "'"
				  << std:: endl;
			return default_value;
		}

		return default_value;
	}


	int      XmlUtil::getAttr( const QDomElement &node, const QString &name, int default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			bool ok;
			int value = valueString.toInt( &ok );

			if ( !ok )
			{
				std::cerr << "Error: bad integer value in attribute "
					  << qPrintable( node.tagName() ) << ":" << qPrintable( name )
					  << " : '" << qPrintable( valueString ) << "'"
					  << std:: endl;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	uint32_t XmlUtil::getAttr( const QDomElement &node, const QString &name, uint32_t default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			// TODO: Does base-0 do what we want?  I.e. use base determined by format e.g. "0xff"
			bool ok;
			uint32_t value = valueString.toInt( &ok, 0 );

			if ( !ok )
			{
				std::cerr << "Error: bad unsigned integer value in attribute "
					  << qPrintable( node.tagName() ) << ":" << qPrintable( name )
					  << " : '" << qPrintable( valueString ) << "'"
					  << std:: endl;
				return default_value;
			}

			return value;
		}

		return default_value;
	}


	QString  XmlUtil::getAttrI18n( const QDomElement &node, const QString &name, const QString &default_value )
	{
		// TODO: are translations done in a compatable way, so that we can use "_name" attributes?
		return node.attribute( QString("_").append(name), default_value );
	}


	double   XmlUtil::getAttrLength( const QDomElement &node, const QString &name, double default_value )
	{
		QString valueString = node.attribute( name, "" );
		if ( valueString != "" )
		{
			double value;
			QString unitsString;
			QTextStream valueStream( &valueString, QIODevice::ReadOnly );

			valueStream >> value >> unitsString;

			if ( !Units::isIdValid( unitsString ) )
			{
				std::cerr << "Error: bad length value in attribute "
					  << qPrintable( node.tagName() ) << ":" << qPrintable( name )
					  << " : '" << qPrintable( valueString ) << "'"
					  << std:: endl;
				return default_value;
			}

			Units *units = Units::fromId( unitsString );

			return value * units->pointsPerUnit();
		}

		return default_value;
	}


	void     XmlUtil::setAttr( const QDomElement &node, const QString &name, const char *value )
	{
		// TODO
	}


	void     XmlUtil::setAttr( const QDomElement &node, const QString &name, const QString &value )
	{
		// TODO
	}


	void     XmlUtil::setAttr( const QDomElement &node, const QString &name, double value )
	{
		// TODO
	}


	void     XmlUtil::setAttr( const QDomElement &node, const QString &name, bool value )
	{
		// TODO
	}


	void     XmlUtil::setAttr( const QDomElement &node, const QString &name, int value )
	{
		// TODO
	}


	void     XmlUtil::setAttr( const QDomElement &node, const QString &name, uint32_t value )
	{
		// TODO
	}


	void     XmlUtil::setAttrLength( const QDomElement &node, const QString &name, double value )
	{
		// TODO
	}

}
