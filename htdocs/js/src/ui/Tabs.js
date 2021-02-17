 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {Tab} from './Tab.js';

export class Tabs extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			current:this.props.active!==undefined?this.props.active:0
		}
	}
	
	changeTab(idx) {
		this.setState({current:idx});
	}
	
	renderTabs() {
		return React.Children.map(this.props.children, (child,i) => {
			if(child.type!=Tab)
				return;
			
			return (<li key={i} className={this.state.current==i?'selected':''} onClick={ () => { this.changeTab(i) } }>{child.props.title}</li>);
		});
	}
	
	renderTabsContent() {
		if(this.props.render)
			return this.props.render(this.state.current);
		
		return React.Children.map(this.props.children, (child,i) => {
			if(child.type!=Tab)
				return;
			
			if(i!=this.state.current)
				return (<div className="s-tabs-content" style={{display: 'none'}}>{child.props.children}</div>);
			
			return (<div className="s-tabs-content" style={{display: 'block'}}>{child.props.children}</div>);
		});
	}
	
	render() {
		return (
			<div>
				<ul className="s-tabs">
					{this.renderTabs()}
				</ul>
				{this.renderTabsContent()}
			</div>
		);
	}
}
