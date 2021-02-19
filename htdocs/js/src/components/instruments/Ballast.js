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

import {App} from '../base/App.js';
import {GaugeDel} from '../../ui/GaugeDel.js';

export class Ballast extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.fill = this.fill.bind(this);
		this.empty = this.empty.bind(this);
		
		App.registerComponent("ballast", this);
	}
	
	fill(e) {
		App.api.command({component: "ballast", action: "fill"});
	}
	
	empty(e) {
		App.api.command({component: "ballast", action: "empty"});
	}
	
	render() {
		if(this.state.ballast===undefined)
			return null;
		
		return (
			<div className="Ballast container">
				<div className="legend">Ballast</div>
				<div className="external_shell">
					<div className="water" style={{top: (100-this.state.ballast.fill*100)+'%'}}></div>
					<div className="internal_shell"></div>
				</div>
				<div className="control">
					<span className="empty fa fa-minus" onClick={this.empty}></span>
					&#160;&#160;&#160;
					<span className="fill fa fa-plus" onClick={this.fill}></span>
				</div>
			</div>
		);
	}
}
